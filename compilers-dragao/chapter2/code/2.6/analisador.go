package main

import (
	"bytes"
	"flag"
	"fmt"
	"os"
	"unicode"
)

var (
	fileName string
	buffer   []byte
)

func main() {
	flag.StringVar(&fileName, "file-name", "teste.txt", "File name")

	flag.Parse()

	f, err := os.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	buffer = f
	lexer := NewLexer()

	for {
		t, ok := lexer.Scan()
		if !ok {
			return
		}

		fmt.Printf("%+v\n", t)
	}
}

type Tag int

const (
	TOKEN_NUM = iota + 255
	TOKEN_FLOAT
	TOKEN_TRUE
	TOKEN_FALSE
	TOKEN_ID
	TOKEN_LT
	TOKEN_LE
	TOKEN_EQUAL
	TOKEN_NEQUAL
	TOKEN_GE
	TOKEN_GT
	TOKEN_ASSIG
)

type Lexer struct {
	Line    int
	Peek    byte
	PBuffer int
	Words   map[string]Token
}

type Token struct {
	TokenTag Tag
	Value    any
}

func NewLexer() *Lexer {
	lexer := &Lexer{
		Line:    1,
		Peek:    ' ',
		PBuffer: -1,
		Words:   make(map[string]Token),
	}

	lexer.Reserve(TOKEN_TRUE, "true")
	lexer.Reserve(TOKEN_FALSE, "false")
	return lexer
}

func (l *Lexer) Reserve(tag Tag, word string) {
	l.Words[word] = Token{tag, word}
}

func (l *Lexer) Scan() (Token, bool) {
	if ok := l.Read(); !ok {
		return Token{}, ok
	}

	if ok := l.TrimSpaceAndComments(); !ok {
		return Token{}, ok
	}

	if IsDigit(l.Peek) || l.Peek == '.' {
		value := 0
		for IsDigit(l.Peek) {
			value = 10*value + int(l.Peek-'0')
			if ok := l.Read(); !ok {
				break
			}
		}

		fraction := 0.0
		power := 1.0
		if l.Peek == '.' {
			if l.Read(); !IsDigit(l.Peek) {
				l.Unread()
			} else {
				for IsDigit(l.Peek) {
					fraction = 10*fraction + float64(l.Peek-'0')
					power *= 10.0
					if ok := l.Read(); !ok {
						break
					}
				}
			}
			return Token{TokenTag: TOKEN_FLOAT, Value: float64(value) + fraction/power}, true
		} else {
			return Token{TokenTag: TOKEN_NUM, Value: value}, true
		}
	}

	if IsLetter(l.Peek) {
		var buf bytes.Buffer
		for IsLetter(l.Peek) {
			_ = buf.WriteByte(l.Peek)
			if ok := l.Read(); !ok {
				break
			}
		}

		str := buf.String()
		if w, exists := l.Words[str]; exists {
			return w, true
		}

		l.Reserve(TOKEN_ID, str)

		return l.Words[str], true
	}

	switch l.Peek {
	case '<':
		l.Read()
		if l.Peek != '=' {
			l.Unread()
			return Token{TokenTag: TOKEN_LT, Value: "<"}, true
		} else {
			return Token{TokenTag: TOKEN_LE, Value: "<="}, true
		}
	case '>':
		l.Read()
		if l.Peek != '=' {
			l.Unread()
			return Token{TokenTag: TOKEN_GT, Value: ">"}, true
		} else {
			return Token{TokenTag: TOKEN_GE, Value: ">="}, true
		}
	case '=':
		l.Read()
		if l.Peek != '=' {
			l.Unread()
			return Token{TokenTag: TOKEN_ASSIG, Value: "="}, true
		} else {
			return Token{TokenTag: TOKEN_EQUAL, Value: "=="}, true
		}
	case '!':
		l.Read()
		if l.Peek != '=' {
			l.Unread()
		} else {
			return Token{TokenTag: TOKEN_NEQUAL, Value: "!="}, true
		}
	}

	t := Token{TokenTag: -1, Value: l.Peek}
	return t, true
}

func (l *Lexer) TrimSpaceAndComments() bool {
	for {
		switch l.Peek {
		case ' ', '\t':
		case '/':
			if ok := l.Read(); !ok {
				return ok
			}

			if l.Peek == '/' {
				if ok := l.TrimCurrentLine(); !ok {
					return ok
				}
			} else if l.Peek == '*' {
				if ok := l.TrimMultilineComment(); !ok {
					return ok
				}
			} else {
				l.Unread()
				return true
			}

		case '\n':
			l.Line += 1
		default:
			return true
		}

		if ok := l.Read(); !ok {
			return ok
		}
	}
}

func (l *Lexer) TrimCurrentLine() bool {
	for {
		if ok := l.Read(); !ok {
			return ok
		}

		if l.Peek == '\n' {
			l.Line += 1
			return true
		}
	}
}

func (l *Lexer) TrimMultilineComment() bool {
	for {
		if ok := l.Read(); !ok {
			return ok
		}

		if l.Peek == '*' {
			if ok := l.Read(); !ok {
				return ok
			}

			if l.Peek == '/' {
				return true
			} else {
				l.Unread()
			}
		}
	}
}

func (l *Lexer) Read() bool {
	if l.PBuffer < 0 {
		l.PBuffer = 0
		l.Peek = buffer[l.PBuffer]
		return true
	}

	l.PBuffer += 1
	if l.PBuffer >= len(buffer) {
		return false
	}

	l.Peek = buffer[l.PBuffer]
	return true
}

func (l *Lexer) Unread() {
	if l.PBuffer > 0 {
		l.PBuffer -= 1
		l.Peek = buffer[l.PBuffer]
	}
}

func IsDigit(b byte) bool {
	return b >= '0' && b <= '9'
}

func IsLetter(b byte) bool {
	return unicode.IsLetter(rune(b))
}
