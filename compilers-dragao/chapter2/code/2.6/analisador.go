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
		fmt.Printf("%+v\n", t)
		if !ok {
			return
		}
	}
}

type Tag int

const (
	TOKEN_NUM = iota + 255
	TOKEN_TRUE
	TOKEN_FALSE
	TOKEN_ID
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
		Peek:    buffer[0],
		PBuffer: 0,
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
	ok := true
	for {
		if l.Peek == ' ' || l.Peek == '\t' {

		} else if l.Peek == '\n' {
			l.Line += 1
		} else {
			break
		}

		if ok = l.Read(); !ok {
			return Token{}, false
		}
	}

	if IsDigit(l.Peek) {
		value := 0
		for IsDigit(l.Peek) {
			value = 10*value + int(l.Peek-'0')
			if ok := l.Read(); !ok {
				break
			}
		}

		return Token{TokenTag: TOKEN_NUM, Value: value}, ok
	}

	if IsLetter(l.Peek) {
		var buf bytes.Buffer
		for IsLetter(l.Peek) {
			_ = buf.WriteByte(l.Peek)
			if ok = l.Read(); !ok {
				break
			}
		}

		str := buf.String()
		if w, exists := l.Words[str]; exists {
			return w, ok
		}

		l.Reserve(TOKEN_ID, str)

		return l.Words[str], ok
	}

	t := Token{TokenTag: -1, Value: l.Peek}
	l.Peek = ' '
	return t, l.PBuffer < len(buffer)
}

func (l *Lexer) Read() bool {
	l.PBuffer += 1
	if l.PBuffer >= len(buffer) {
		return false
	}

	l.Peek = buffer[l.PBuffer]
	return true
}

func IsDigit(b byte) bool {
	return b >= '0' && b <= '9'
}

func IsLetter(b byte) bool {
	return unicode.IsLetter(rune(b))
}
