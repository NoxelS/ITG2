# usr/bin/python3
import copy

# BNF Syntax
BNFSYMBOLS = dict()
BNFSYMBOLS['assign'] = '->'  # standard is "::="
BNFSYMBOLS['comment'] = '#'  # could also be "//"
BNFSYMBOLS['epsilon'] = '@'  # could also be "//"


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

    for nonterm in grammar['nonterms']:
        for option in grammar['productions'][nonterm]:
            updated = True
            while updated:
                updated = False
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
    follow_dict['S'] = set('$')

    # Update follow_dict until it doesn't change anymore.
    # TODO

    return follow_dict


def gen_parsetable(grammar):
    pass


def parse(grammar, string):
    pass


# Generate grammar from file.
grammar = gen_grammar_from_file('filebase.y')

# Generate first dictionary.
first_dict = gen_first_dict(grammar)
follow_dict = gen_follow_dict(grammar, first_dict)

print(follow_dict)
