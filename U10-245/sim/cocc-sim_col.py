#!/usr/bin/env python3
#
# COCC assembler simulator
#
# 04/2021 Ch. Hoffmann
#
# @20210706
########################################################################                      
#
# Shortcuts:
#  q         = Quit w/o continuing
#  r         = reset
#  s         = start/stop simulation
#  +         = increase sim speed
#  -         = decrease sim speed
#  ' , \n    = step sim
# UP/DOWN    = navigate code
# RIGHT/LEFT = navigate output
########################################################################                      
                      

########################################################################
import re
import sys
import math
import curses as cs
from copy import deepcopy 
from collections import OrderedDict
########################################################################


###########################################################
def intconv(v):
  if v.startswith("0x"):
    return int(v, 16)
  elif v.startswith("0b"):
    return int(v, 2)
  else:
    return int(v)
###########################################################


###########################################################
class cpu:
  MEM_SIZE = 256
  asmfile = sys.argv[1]

  # ASM definitions
  cmdlen = {
    "nop":   1,
    "hlt":   1,
    "call":  2,
    "ret":   1,
    "cmp":   1,
    "mout":  2,
    "min":   2,
    "add":   1,
    "adc":   1,
    "sub":   1,
    "inc":   1,
    "dec":   1,
    "and":   1,
    "or":    1,
    "xor":   1,
    "shl":   1,
    "shr":   1,
    "rol":   1,
    "ror":   1,
    "not":   1,
    "mlo":   1,
    "mhi":   1,
    "sqrt":  1,
    "ldi":   2,
    "ldx":   2,
    "stx":   2,
    "lda":   1,		# lda R  = copy *RegA to R
    "sta":   1,		# sta R  = copy R to *RegA
    "push":  1,
    "pop":   1,
    "jmp":   2,
    "jz":    2,
    "jnz":   2,
    "je":    2,
    "jne":   2,
    "jc":    2,
    "jnc":   2,
    "rout":  1,
    "rin":   1,
    "mov":   1
  } 

  cmdtics = {
    "nop":   3,
    "hlt":   3,
    "call":  8,
    "ret":   6,
    "cmp":   4,
    "mout":  6,
    "min":   6,
    "add":   5,
    "adc":   5,
    "sub":   5,
    "inc":   5,
    "dec":   5,
    "and":   5,
    "or":    5,
    "xor":   5,
    "shl":   5,
    "shr":   5,
    "rol":   5,
    "ror":   5,
    "not":   5,
    "mlo":   5,
    "mhi":   5,
    "sqrt":  5,
    "ldi":   5,
    "ldx":   6,
    "stx":   6,
    "lda":   5,
    "sta":   5,		
    "push":  5,
    "pop":   6,
    "jmp":   5,
    "jz":    5,
    "jnz":   5,
    "je":    5,
    "jne":   5,
    "jc":    5,
    "jnc":   5,
    "rout":  4,
    "rin":   4,
    "mov":   4
  } 

  token = {
    "nop":   0b00000000,
    "hlt":   0b00000001,
    "call":  0b00000010,
    "ret":   0b00000011,
    "cmp":   0b00000100,
    "mout":  0b00000101,
    "min":   0b00000110,
    "add":   0b00010000,
    "adc":   0b00010001,
    "sub":   0b00010010,
    "inc":   0b00010011,
    "dec":   0b00010100,
    "and":   0b00010101,
    "or":    0b00010110,
    "xor":   0b00010111,
    "shl":   0b00011000,
    "shr":   0b00011001,
    "rol":   0b00011010,
    "ror":   0b00011011,
    "not":   0b00011100,
    "mlo":   0b00011101,
    "mhi":   0b00011110,
    "sqrt":  0b00011111,
    "ldi":   0b01000000,
    "ldx":   0b01001000,
    "stx":   0b01010000,
    "lda":   0b00100000,	
    "sta":   0b00101000,	
    "push":  0b01011000,
    "pop":   0b01100000,
    "jmp":   0b01101000,
    "jz":    0b01101001,
    "jnz":   0b01101010,
    "je":    0b01101001,
    "jne":   0b01101010,
    "jc":    0b01101011,
    "jnc":   0b01101100,
    "rout":  0b01110000,
    "rin":   0b01111000,
    "mov":   0b10000000
  } 

  regs = {
    "A": 0b000,
    "B": 0b001,
    "C": 0b010,
    "D": 0b011,
    "E": 0b100,
    "F": 0b101,
    "G": 0b110,
    "H": 0b111
  }

  def __init__(self):
    self.cocc_PC = 0
    self.cocc_ZF = 0
    self.cocc_CF = 0
    self.cocc_RAM        = [0 for _ in range(self.MEM_SIZE)]
    self.cocc_RAM_CmdLen = [0 for _ in range(self.MEM_SIZE)]
    self.cocc_RAM_ColMat = [0 for _ in range(self.MEM_SIZE)]
    self.cocc_Regs       = {'A':0, 'B':0, 'C':0, 'D':0, 'E':0, 'F':0, 'G':0, 'H':0}
    self.cocc_stack      = []
    self.data   = OrderedDict()
    self.labels = {}
    self.prog   = {}
    self.cocc_tics = 0
    
    TEXT, DATA = 0, 1
    cnt = 0
    with open(self.asmfile) as f:
      for l in f:
        l = re.sub(";.*", "", l)
        l = l.strip()
        if l == "":
          continue

        if l == ".text":
          section = TEXT
        elif l == ".data":
          section = DATA
        else:
          if section == DATA:
            n, v = map(str.strip, l.split("=", 2))
            self.data[str(n)] = intconv(v)
          elif section == TEXT:
            kw = l.split()
            if kw[0][-1] == ":":
              self.labels[kw[0].rstrip(":")] = cnt
            else:
              current_inst = kw[0]

              if current_inst == "ldi":
                op1 = self.regs[kw[1]]
                kw[0] = (self.token[kw[0]] & 0b11111000) | op1
                del kw[1]
                if kw[1][0] != '%':
                  kw[1] = intconv(kw[1])
              elif current_inst in ("ldx", "stx", "push", "pop"):
                op1 = self.regs[kw[1]]
                kw[0] = (self.token[kw[0]] & 0b11111000) | op1
                del kw[1]
              elif current_inst in ("mout", "min"):
                kw[0] = (self.token[kw[0]] & 0b11111111)
              elif current_inst in ("rout", "rin"):
                r = self.regs[kw[1]]
                kw[0] = (self.token[kw[0]] & 0b11111000) | r
                del kw[1]
              elif current_inst == "mov":
                op1 = self.regs[kw[1]]
                op2 = self.regs[kw[2]]
                kw[0] = (self.token[kw[0]] & 0b11111000) | op2
                kw[0] = (kw[0] & 0b11000111) | (op1 << 3)
                del kw[2]
                del kw[1]
              elif current_inst in ("lda", "sta"):
                r = self.regs[kw[1]]
                kw[0] = (self.token[kw[0]] & 0b11111000) | r
                del kw[1]
              else:
                kw[0] = self.token[kw[0]]

              # write text segment into RAM-map
              # write cmd-lengths into memcmdlen-map
              self.prog[cnt] = l.split()
              self.cocc_RAM_CmdLen[cnt] = self.cmdlen[l.split()[0]]
              for a in kw:
                self.cocc_RAM[cnt] = a
                cnt += 1
    
    # Write data segment into RAM-map
    self.label2addr = {}
    for k,v in self.data.items():
      self.label2addr[k] = cnt
      self.cocc_RAM[cnt] = v
      cnt += 1

    # combine variables and labels
    self.label2addr.update(self.labels)
    
    # Replace labels in RAM-map by addresses
    for i, b in enumerate(self.cocc_RAM):
      if str(b).startswith("%"):
        self.cocc_RAM[i] = self.label2addr[b.lstrip("%")]

    # create color matrix for RAM-map
    for addr in range(self.MEM_SIZE):
      if addr in self.labels.values():
        self.cocc_RAM_ColMat[addr] |= 1048576 | 512  	# cs.dim | cs.color_pair(2) # 2 5 6 7
      elif addr in [self.label2addr[v] for v in self.data]:
        self.cocc_RAM_ColMat[addr] |= 1048576 | 1792 	# cs.dim | cs.color_pair(7) 

    # codeline to addr map (line2addr)
    # addr to codeline map (addr2line)
    self.line2addr = {}
    self.addr2line = {}
    self.proglen = 0
    self.progstr = []
    line = 0
    for pc in self.prog:
      self.line2addr[line] = pc
      self.addr2line[pc] = line
      if pc in self.labels.values():
        key = list(self.labels.keys())[list(self.labels.values()).index(pc)]
        self.progstr.append('0x%02X ' % pc + "%-10s" % (key[0:8]+':') + (' '.join(self.prog[pc])))
      else:
        self.progstr.append('0x%02X ' % pc + "          " + (' '.join(self.prog[pc])))
      line += 1
    self.proglen = len(self.progstr)
###########################################################


########################################################################
def run_step(s, p, dpc):
  p.cocc_PC += dpc		# next instruction's PC
  ci = p.prog[p.cocc_PC]	# current instruction line
  ci0 = ci[0].lower()		# kw0 = instruction
  if len(ci) > 1:
    ci1r = ci[1].upper()	# kw1 = register (A..G)
    ci1m = ci[1][1:]		# kw1 = label of mem_addr (%label)
  if len(ci) > 2:
    ci2n = ci[2].lower()	# kw2 = immediate (0x...)
    ci2r = ci[2].upper()	# kw2 = register (A..G)
    ci2m = ci[2][1:]		# kw2 = label of mem_addr (%label)

  if ci0 == "hlt":
    delta_PC = 99999;		# code end
  elif ci0 == "nop":
    delta_PC = 1

  # Data-Transfer-Group
  elif ci0 == "ldi":
    if ci[2][0] == '%':
      p.cocc_Regs[ci1r] = int( p.label2addr[ci2m] )
    else:
      p.cocc_Regs[ci1r] = intconv(ci2n)
    delta_PC = 2
  elif ci0 == "mov":
    p.cocc_Regs[ci1r] = p.cocc_Regs[ci2r]
    delta_PC = 1
  elif ci0 == "ldx":
    p.cocc_Regs[ci1r] = int(p.cocc_RAM[ p.label2addr[ci2m] ])
    delta_PC = 2
  elif ci0 == "stx":
    p.cocc_RAM[ p.label2addr[ci2m] ] = int(p.cocc_Regs[ci1r])
    delta_PC = 2
# XXX
  elif ci0 == "lda":
    p.cocc_Regs[ci1r] = int(p.cocc_RAM[ p.cocc_Regs['A'] ])
    delta_PC = 1
  elif ci0 == "sta":
    p.cocc_RAM[ p.cocc_Regs['A'] ] = int(p.cocc_Regs[ci1r])
    delta_PC = 1


  # Stack-Operation-Group
  elif ci0 == "pop":
    if len(p.cocc_stack) > 0:
      p.cocc_Regs[ci1r] = p.cocc_stack.pop()
    delta_PC = 1
  elif ci0 == "push":
    p.cocc_stack.append(int(p.cocc_Regs[ci1r]))
    delta_PC = 1

  # IO-Group
  elif ci0 == "mout":
    s.output.append(int(p.cocc_RAM[p.label2addr[ci1m]]))
    s.OutLen += 1
    delta_PC = 2
  elif ci0 == "min":
    s.redraw(p)
    try:
      win0 = cs.newwin(3,13,32,22)
      win0.border()
      cs.echo()
      win0.addstr(1, 1, "INPUT:    ")
      win0.refresh()
      input = int(win0.getstr(1, 8, 3)) & 0xff
      cs.noecho()
      del win0
    except:
      input = 0
    p.cocc_RAM[p.label2addr[ci1m]] = input
    delta_PC = 2
  elif ci0 == "rout":
    s.output.append(int(p.cocc_Regs[ci1r]))
    s.OutLen += 1
    delta_PC = 1
  elif ci0 == "rin":
    s.redraw(p)
    try:
      win0 = cs.newwin(3,13,32,22)
      win0.border()
      cs.echo()
      win0.addstr(1, 1, "INPUT:    ")
      win0.refresh()
      input = int(win0.getstr(1, 8, 3)) & 0xff
      cs.noecho()
      del win0
    except:
      input = 0
    p.cocc_Regs[ci1r] = input
    delta_PC = 1

  # Jump+Branch-Group
  elif ci0 == "call":
    p.cocc_stack.append(int(p.cocc_PC)+2)
    delta_PC = p.label2addr[ci1m] - p.cocc_PC
  elif ci0 == "ret":
    delta_PC = p.cocc_stack.pop() - p.cocc_PC
  elif ci0 == "jmp":
    delta_PC = p.label2addr[ci1m] - p.cocc_PC
  elif ci0 == "jz" or ci0 == "je":
    if p.cocc_ZF == 1:
      delta_PC = p.label2addr[ci1m] - p.cocc_PC
    else:
      delta_PC = 2
  elif ci0 == "jnz" or ci0 == "jne":
    if p.cocc_ZF == 0:
      delta_PC = p.label2addr[ci1m] - p.cocc_PC
    else:
      delta_PC = 2
  elif ci0 == "jc":
    if p.cocc_CF == 1:
      delta_PC = p.label2addr[ci1m] - p.cocc_PC
    else:
      delta_PC = 2
  elif ci0 == "jnc":
    if p.cocc_CF == 0:
      delta_PC = p.label2addr[ci1m] - p.cocc_PC
    else:
      delta_PC = 2

  # ALU-Group
  elif ci0 == "add":
    v = int(p.cocc_Regs['A']) + int(p.cocc_Regs['B'])
    p.cocc_Regs['A'] = v & 0xff
    p.cocc_CF = (v >> 8) & 0x1
    delta_PC = 1
  elif ci0 == "adc":
    v = int(p.cocc_Regs['A']) + int(p.cocc_Regs['B']) + p.cocc_CF
    p.cocc_Regs['A'] = v & 0xff
    p.cocc_CF = (v >> 8) & 0x1
    delta_PC = 1
  elif ci0 == "sub":
    v = int(p.cocc_Regs['A']) - int(p.cocc_Regs['B'])
    p.cocc_Regs['A'] = v & 0xff
    p.cocc_CF = (v >> 8) & 0x1
    delta_PC = 1
  elif ci0 == "inc":
    v = int(p.cocc_Regs['A']) + 1
    p.cocc_Regs['A'] = v & 0xff
    p.cocc_CF = (v >> 8) & 0x1
    delta_PC = 1
  elif ci0 == "dec":
    v = int(p.cocc_Regs['A']) - 1
    p.cocc_Regs['A'] = v & 0xff
    p.cocc_CF = (v >> 8) & 0x1
    delta_PC = 1
  elif ci0 == "and":
    p.cocc_Regs['A'] &= int(p.cocc_Regs['B'])
    delta_PC = 1
  elif ci0 == "or":
    p.cocc_Regs['A'] |= int(p.cocc_Regs['B'])
    delta_PC = 1
  elif ci0 == "xor":
    p.cocc_Regs['A'] ^= int(p.cocc_Regs['B'])
    delta_PC = 1
  elif ci0 == "not":
    p.cocc_Regs['A'] = ~int(p.cocc_Regs['A']) & 0xff
    delta_PC = 1
  elif ci0 == "shl":
    p.cocc_Regs['A'] = int(p.cocc_Regs['A']) << int(p.cocc_Regs['B']) & 0xff
    delta_PC = 1
  elif ci0 == "shr":
    p.cocc_Regs['A'] = int(p.cocc_Regs['A']) >> int(p.cocc_Regs['B']) & 0xff
    delta_PC = 1
  elif ci0 == "rol":
    v = int(p.cocc_Regs['A'])
    p.cocc_Regs['A'] = (((v & 0x80) >> 7) | (v << 1)) & 0xff
    delta_PC = 1
  elif ci0 == "ror":
    v = int(p.cocc_Regs['A'])
    p.cocc_Regs['A'] = (((v & 0x1) << 7) | (v >> 1)) & 0xff
    delta_PC = 1
  elif ci0 == "mlo":
    v = int(p.cocc_Regs['A']) * int(p.cocc_Regs['B'])
    p.cocc_Regs['A'] = v & 0xff
    p.cocc_CF = (v >> 8) & 0x1
    delta_PC = 1
  elif ci0 == "mhi":
    v = int(p.cocc_Regs['A']) * int(p.cocc_Regs['B'])
    p.cocc_Regs['A'] = (v >> 8) & 0xff
    p.cocc_CF = (v >> 16) & 0x1
    delta_PC = 1
  elif ci0 == "sqrt":
    v = int(math.sqrt(int(p.cocc_Regs['A'])))
    p.cocc_Regs['A'] = v & 0xff
    delta_PC = 1
  elif ci0 == "cmp":
    delta_PC = 1

  if ci0 in ["add", "adc", "sub", "inc", "dec", "and", "or", "xor", "not", "shl", "shr", "rol", "ror", "mlo", "mhi", "sqrt"]:
    if int(p.cocc_Regs['A']) == 0:
      p.cocc_ZF = 1
    else:
      p.cocc_ZF = 0
  if ci0 == 'cmp':
    v = int(p.cocc_Regs['A']) - int(p.cocc_Regs['B'])
    if v == 0:
      p.cocc_ZF = 1
    else:
      p.cocc_ZF = 0
    if v < 0:
      p.cocc_CF = 1
    else:
      p.cocc_CF = 0
    delta_PC = 1

  if len(p.cocc_stack) > 0:
    for i,b in enumerate(p.cocc_stack):
      p.cocc_RAM[255-i] = b

  p.cocc_tics += p.cmdtics[ci0]

  return delta_PC
########################################################################


########################################################################
# global window shapes
w1w, w1h, w1x0, w1y0 =  35,      30,             1,     1	# code
w2w, w2h, w2x0, w2y0 = w1w,       8,             1, w1h+1	# output
w4w, w4h, w4x0, w4y0 =  20, w1h+w2h,         w1w+1,     1   	# stack
w6w, w6h, w6x0, w6y0 =  21, w1h+w2h,     w1w+w4w+1,     1	# labels
w3w, w3h, w3x0, w3y0 =  57,       7, w1w+w4w+w6w+1,     1	# register
w5w, w5h, w5x0, w5y0 =  w3w,      20,          w3x0, w3h+1	# mem image
w7w, w7h, w7x0, w7y0 =  w3w,      11,          w3x0, w3h+w5h+1	# aux-window
########################################################################


########################################################################
class screen():

  def reset(self):
    self.CodeListStart = 0
    self.OutListStart = 0
    self.output = []
    self.OutLen = 0

  def __init__(self):
    self.reset()
    self.steptime = 200

    # init screen
    self.scr = cs.initscr()
    cs.resize_term(40,135)
    cs.noecho()
    cs.curs_set(0)
    #  self.scr.immedok(True)
    self.scr.border()
    self.scr.timeout(-1)
    # self.scr.nodelay(1)
    self.scr.keypad(1)
    # cs.cbreak()
    self.scr.refresh()
    
    # for colors
    cs.start_color()
    cs.use_default_colors()
    for i in range(0, cs.COLORS):
      cs.init_pair(i + 1, i, -1)
                          
    # create windows
    win1a = cs.newwin(w1h, w1w, w1y0, w1x0)
    win1a.border()
    win1a.refresh()
    self.win1 = win1a.derwin(w1h-2, w1w-2, 1, 1)

    win2a = cs.newwin(w2h, w2w, w2y0, w2x0)
    win2a.border()
    win2a.refresh()
    self.win2 = win2a.derwin(w2h-2, w2w-2, 1, 1)

    win3a = cs.newwin(w3h, w3w, w3y0, w3x0)
    win3a.border()
    win3a.refresh()
    self.win3 = win3a.derwin(w3h-2, w3w-2, 1, 1)

    win4a = cs.newwin(w4h, w4w, w4y0, w4x0)
    win4a.border()
    win4a.refresh()
    self.win4 = win4a.derwin(w4h-2, w4w-2, 1, 1)

    win5a = cs.newwin(w5h, w5w, w5y0, w5x0)
    win5a.border()
    win5a.refresh()
    self.win5 = win5a.derwin(w5h-2, w5w-2, 1, 1)

    win6a = cs.newwin(w6h, w6w, w6y0, w6x0)
    win6a.border()
    win6a.refresh()
    self.win6 = win6a.derwin(w6h-2, w6w-2, 1, 1)

    win7a = cs.newwin(w7h, w7w, w7y0, w7x0)
    win7a.border()
    win7a.refresh()
    self.win7 = win7a.derwin(w7h-2, w7w-2, 1, 1)


  def redraw(self, p):
    # 1st window (prog)
    str0 = "ASM-CODE"
    self.win1.clear()
    self.win1.addstr(0, 1, str0, cs.A_BOLD)
    for i in range(0,w1h-4):
      if 0 <= self.CodeListStart + i < p.proglen:
        str1 = p.progstr[self.CodeListStart + i] + " "*w1w
        if p.cocc_PC == p.line2addr[self.CodeListStart + i]:
          attr = cs.A_BOLD | cs.A_REVERSE
        else:
          attr = cs.A_DIM
        self.win1.addstr(i+2, 0, str1[0:5], attr | cs.A_BOLD)
        self.win1.addstr(i+2, 5, str1[5:w1w-3], attr)
  
    # 2nd window (output) --ok
    self.win2.clear()
    for i in range(0,w2h-2):
      j = self.OutListStart-(w2h-2)+i
      if j>=0:
        str1 = "%03d: " % j + "0x%02X " % self.output[j] + "(%3d)" % self.output[j]
        self.win2.addstr(i, 0, str1)

    # 3rd window (reg&flags) --ok
    str0 = "REGS & FLAGS                         Tics: " + str(p.cocc_tics)
    str1 = '    '.join(['%c' % a for a in sorted(p.cocc_Regs)]) + '        ZF  CF'
    str2 = ' '.join(['0x%02X' % int(b) for _,b in sorted(p.cocc_Regs.items())]) + '     ' + str(p.cocc_ZF) + '   ' + str(p.cocc_CF)
    str3 = '  '.join(['%-3d' % int(b) for _,b in sorted(p.cocc_Regs.items())])
    self.win3.clear()    
    self.win3.addstr(0, 1, str0, cs.A_BOLD)
    self.win3.addstr(2, 1, str1, cs.A_BOLD | cs.A_UNDERLINE)
    self.win3.addstr(3, 1, str2, cs.A_DIM)
    self.win3.addstr(4, 1, str3, cs.A_DIM)
    
    # 4th window (stack) --ok
    str0 = "STACK"
    ls = len(p.cocc_stack)
    hs = w4h-5
    self.win4.clear()    
    self.win4.addstr(0, 1, str0, cs.A_BOLD)
    i = idx = 0
    for i in range(0, min(hs, ls)):
      idx = i + max(0,ls-hs)
      self.win4.addstr(w4h-3-i, 1, "0x%02X" % (255-idx), cs.A_BOLD)
      self.win4.addstr(w4h-3-i, 7, str("0x%02X" % p.cocc_stack[idx]), cs.A_DIM)
      self.win4.addstr(w4h-3-i,12, str("(%3d)" % p.cocc_stack[idx]), cs.A_DIM)
    self.win4.addstr(w4h-3-min(hs, ls), 1, "0x%02X" % (255-idx-1), cs.A_BOLD | cs.A_REVERSE | cs.color_pair(3))
    
    # 5th window (mem image) --ok
    memcol = deepcopy(p.cocc_RAM_ColMat)
    memcol[255-len(p.cocc_stack)] = cs.A_BOLD | cs.A_REVERSE | cs.color_pair(3)
    if p.cocc_RAM_CmdLen[p.cocc_PC] == 2 and p.cocc_PC < p.MEM_SIZE-1:
      memcol[p.cocc_PC+1] = cs.A_BOLD | cs.A_REVERSE
    memcol[p.cocc_PC] = cs.A_BOLD | cs.A_REVERSE
    self.win5.clear()    
    self.win5.addstr(0, 1, "RAM IMAGE", cs.A_BOLD)
    for i in range(0,16):
      self.win5.addstr(i+2, 1, "0x%02X" % (16*i), cs.A_BOLD)
      for j in range(0,16):
        addr = 16*i+j
        self.win5.addstr(i+2, 7+j*3, "%02X" % p.cocc_RAM[addr], memcol[addr])
        
    # 6th window (labels + vars) --ok
    self.win6.clear()    
    self.win6.addstr(0, 1, "VARS & LABELS", cs.A_BOLD)
    self.win6.addstr(2, 1, "NAME     ADDR VAL", cs.A_UNDERLINE | cs.A_BOLD)
    pos = 2
    for i,v in enumerate(p.data):
      if pos+12 < w6h:
        pos += 1
        str1 = "%%%-7s" % v
        str2 = "0x%02X" % p.label2addr[v]
        str3 = "%3d"    % p.cocc_RAM[p.label2addr[v]] 
        self.win6.addstr(pos, 1, str1, cs.A_DIM)
        self.win6.addstr(pos,10, str2, cs.color_pair(7))
        self.win6.addstr(pos,15, str3, cs.A_DIM)
      else:
        self.win6.addstr(pos+1, 10, "...", cs.A_DIM)
    pos += 2
    self.win6.addstr(pos, 1, "NAME         ADDR", cs.A_UNDERLINE | cs.A_BOLD)
    for i,v in enumerate(sorted(p.labels.items())):
      if pos+5 <= w6h:
        pos += 1
        str1 = "%-12s" % v[0]
        str2 = "0x%02X" % v[1]
        self.win6.addstr(pos,  1, str1, cs.A_DIM)
        self.win6.addstr(pos, 14, str2, cs.color_pair(2))
      else:
        self.win6.addstr(pos+1, 10, "...", cs.A_DIM)
    
    # 7th window (shortcuts) --ok
    self.win7.addstr(0, 1, "Shortcuts")
    self.win7.addstr(1, 1, " q          quit")
    self.win7.addstr(2, 1, " r          reset")
    self.win7.addstr(3, 1, " s          start/stop simulation")
    self.win7.addstr(4, 1, " +/-        simulation speed (%2d)" % (10-self.steptime/50))
    self.win7.addstr(5, 1, " SPACE/RET  single step, stop continuous")
    self.win7.addstr(6, 1, " UP/DOWN    navigate code")
    self.win7.addstr(7, 1, " LEFT/RIGHT navigate output")

    self.win1.noutrefresh()
    self.win2.noutrefresh()
    self.win3.noutrefresh()
    self.win4.noutrefresh()
    self.win5.noutrefresh()
    self.win6.noutrefresh()
    self.win7.noutrefresh()
    cs.doupdate()

  def if_loop(self, p):
    contsim = False
    dpc = 0

    while True:
      self.redraw(p)

      if contsim and dpc==99999:
        contsim = False
        self.scr.timeout(-1)

      event = self.scr.getch()
      cs.flushinp
      if event == ord("q") or event == 0x1b:	# Quit w/o continuing
        cs.endwin()
        return False
      elif event == ord('r'):			# reset
        return True
      elif event == cs.KEY_UP:
        self.CodeListStart = max(self.CodeListStart - 1, -w1h + 10)
      elif event == cs.KEY_DOWN:
        self.CodeListStart = min(self.CodeListStart + 1, p.proglen - 6)
      elif event == cs.KEY_LEFT:
        self.OutListStart = max(self.OutListStart-1, 0)
      elif event == cs.KEY_RIGHT:
        self.OutListStart = min(self.OutListStart+1, self.OutLen)
      elif event == ord('s'):			# start/stop simulation
        contsim = not contsim
        if contsim:
          self.scr.timeout(self.steptime)
        else:
          self.scr.timeout(-1)
      elif event == ord('+'):			# increase sim speed
        self.steptime = max(self.steptime-50,0)
        if contsim:
          self.scr.timeout(self.steptime)
      elif event == ord('-'):			# decrease sim speed
        self.steptime = min(self.steptime+50,500)
        if contsim:
          self.scr.timeout(self.steptime)
      elif event == ord(' ') or event == ord('\n') or contsim == True:	# step sim
        if dpc != 99999:
          dpc = run_step(self, p, dpc)

        if contsim and event == ord(' '):
          contsim = False
          self.scr.timeout(-1)

        # focus on new output
        self.OutListStart = self.OutLen

        # center next code step when outside display
        if p.addr2line[p.cocc_PC] - self.CodeListStart > w1h-7 \
           or p.addr2line[p.cocc_PC] - self.CodeListStart < 0:
          self.CodeListStart = p.addr2line[p.cocc_PC] - (w1h-20)
########################################################################


########################################################################
# resize x-window
#sys.stdout.write("\x1b[8;{rows};{cols}t\n".format(rows=41, cols=136))
#sys.stdout.write("reset\n")
sys.stdout.write("gnome-terminal --full-screen\n")
myprog = cpu()
myscrn = screen()
do_run = 1
while do_run:
  do_run = myscrn.if_loop(myprog)
  myprog.__init__()
  myscrn.reset()
cs.endwin()
#sys.stdout.write("\x1b[8;{rows};{cols}t\n".format(rows=25, cols=80))
########################################################################
