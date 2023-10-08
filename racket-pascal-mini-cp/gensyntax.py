l = [
    "and",
    "begin",
    "div",
    "do",
    "else",
    "end",
    "for",
    "function",
    "if",
    "in",
    "nil",
    "not",
    "of",
    "procedure",
    "program",
    "repeat",
    "set",
    "then",
    "to",
    "until",
    "var",
    "while",
]


for f in l:
    stx = f"""
(define stx-keyword-{f}
 (syntax-item
  "keyword-{f}" 0
  (lambda (tok)
    (and (eq? (token-type tok) token-keyword)
        (eq? (token-attribute tok) "{f}")))))
    """
    print(stx)

l2 = [
    "leq",
    "geq",
    "lt",
    "gt",
    "neq",
    "eq",
    "assign",
    "double-dot",
    "dot",
    "plus",
    "minus",
    "multi",
    "divide",
]

for f in l2:
    stx = f"""
(define stx-relop-{f}
 (syntax-item
  "keyword-{f}" 0
  (lambda (tok)
    (and (eq? (token-type tok) token-relop)
        (eq? (token-attribute tok) "{f}")))))
    """
    print(stx)


l3 = [
    "square-lbracket",
    "square-rbracket",
    "rbracket",
    "lbracket",
    "semicolon",
    "comma",
]

for f in l3:
    stx = f"""
(define stx-sep-{f}
 (syntax-item
  "keyword-{f}" 0
  (lambda (tok)
    (and (eq? (token-type tok) token-sep)
        (eq? (token-attribute tok) "{f}")))))
    """
    print(stx)
