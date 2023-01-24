# usr/bin/python3

import copy


# BNF Syntax
BNFSYMBOLS = dict()
BNFSYMBOLS['assign'] = '->'  # standard is "::="
BNFSYMBOLS['comment'] = '#'  # could also be "//"
BNFSYMBOLS['epsilon'] = '@'  # could also be "//"
BNFSYMBOLS['start'] = 'S'

# Utils

def print_dict(d, name=None):
    if name:
        print(name, ":")
    for key, value in d.items():
        if name:
            print("\t", end="")
        print(key, " -> ", value)


def gen_grammar(string):
    """Generate a productions for a given BNF string."""
    productions = dict()
    terms = set()
    nonterms = set()

    for line in string.splitlines():
        if line:
            line = line.strip()
            # Ignore lines starting with a comment symbol.
            if line[0] == '#':
                continue
            lhs, rhs = [_.strip() for _ in line.split(BNFSYMBOLS['assign'])]

            # Make set of all options for this lhs.
            productions[lhs] = set()

            # Add options of rhs to the set.
            if '|' in rhs:
                for option in rhs.split('|'):
                    productions[lhs].add(option.strip())
            else:
                productions[lhs].add(rhs.strip())

            # Add lhs to nonterms.
            nonterms.add(lhs)

    # Add all terms to terms.
    for lhs, rhs in productions.items():
        for option in rhs:
            for term in option:
                if term not in nonterms and term != BNFSYMBOLS['epsilon']:
                    terms.add(term)

    grammar = dict()
    grammar['productions'] = productions
    grammar['nonterms'] = nonterms
    grammar['terms'] = terms

    return grammar


def gen_grammar_from_file(filename):
    """Generate a productions for a given BNF file."""
    with open(filename, 'r') as f:
        return gen_grammar(f.read())


def gen_first_dict(grammar):
    first_dict = dict()

    # Regel 1: Wenn ein Terminal in der Produktion steht, dann ist es das erste Terminal.
    for term in grammar['terms']:
        first_dict[term] = set(term)

    # Regel 2: A -> epsilon ist das erste Terminal.
    for nonterm in grammar['nonterms']:
        first_dict[nonterm] = set()

        if BNFSYMBOLS['epsilon'] in grammar['productions'][nonterm]:
            first_dict[nonterm].add(BNFSYMBOLS['epsilon'])

    first_dict_copy = {}
    while first_dict_copy != first_dict:
        first_dict_copy = copy.deepcopy(first_dict)
        for nonterm in grammar['nonterms']:
            for option in grammar['productions'][nonterm]:
                for symbol in option:
                    if symbol in grammar['terms']:
                        first_dict[nonterm].add(symbol)
                        break
                    elif symbol in grammar['nonterms']:
                        first_dict[nonterm] = first_dict[nonterm].union(
                            first_dict[symbol])
                        if BNFSYMBOLS['epsilon'] not in first_dict[symbol]:
                            break

    return first_dict


def gen_follow_dict(grammar, first_dict=None):
    follow_dict = dict()
    first_dict = first_dict if first_dict else gen_first_dict(grammar)

    for nonterm in grammar['nonterms']:
        follow_dict[nonterm] = set()

    # Regel 1: Follow(S) = { $ }
    follow_dict[BNFSYMBOLS['start']] = set('$')

    old_dict = {}
    while old_dict != follow_dict:
        old_dict = copy.deepcopy(follow_dict)

        for derivative in grammar['nonterms']:
            for production in grammar['productions'][derivative]:
                if any(B in grammar['nonterms'] for B in production): # Check if there are any nonterms
                    for i, cursor in enumerate(production):
                        # print(f"{derivative} -> {i}: {cursor}")
                        if cursor in grammar['nonterms']:
                            # Cursor points to nonterm -> Cursor = B
                            alpha = production[0:i] # We don't need that, only for debugging
                            beta = production[i+1:len(production)]
                            B = cursor

                            # Regel 2 A => aBb
                            if beta:
                                for b in beta:  # beta could be a string of terminals and nonterms
                                    follow_dict[B] = follow_dict[B].union(first_dict[b] - {BNFSYMBOLS['epsilon']})

                            # Regel 3 A => aB | A => aBb & B => ep
                            if B in grammar['nonterms'] or (beta and BNFSYMBOLS['epsilon'] in grammar['productions'][derivative]):
                                follow_dict[B] = follow_dict[B].union(follow_dict[derivative])
    return follow_dict

def gen_lookahead_dict(grammar, first_dict, follow_dict):
    lookahead_dict = dict()

    for nonterm in grammar['nonterms']:
        for production in grammar['productions'][nonterm]:
            # print(f"First([{production}]Follow({nonterm}))", end=" = ")
            follow_set = follow_dict[nonterm]
            # print(f"First([{production}][{follow_set}])", end=" = ")
            concatination = []
            for B in follow_set:
                concatination.append("".join([production, B]))

            tmp_dict = dict()
            for element in concatination:
                for char in element:
                    if char in grammar['nonterms']:
                        tmp_dict[element] = first_dict[char]
                        if BNFSYMBOLS['epsilon'] not in first_dict[char]:
                            break
                    elif char in grammar['terms']:
                        tmp_dict[element] = set(char)
                        break
            lookahead_dict[nonterm] = tmp_dict


    return lookahead_dict


def gen_parsetable(grammar):
    pass


def parse(grammar, string):
    pass


# Generate grammar from file.
grammar = gen_grammar_from_file('filebase.y')

# Generate first dictionary.
first_dict = gen_first_dict(grammar)
follow_dict = gen_follow_dict(grammar, first_dict)
lookahead_dict = gen_lookahead_dict(grammar, first_dict, follow_dict)

print_dict(grammar, 'Grammar')
print_dict(first_dict, 'First-Set')
print_dict(follow_dict, 'Follow-Set')
print_dict(lookahead_dict, 'Lookahead-Set')