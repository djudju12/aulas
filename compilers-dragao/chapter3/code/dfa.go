package main

/*
	CONSTRUÇÃO DE UM DFA SEGUNDO O ALGORITMO 3.18 - PAGINA 96
*/

import (
	"fmt"
	"log"
)

/* (Q, Σ, δ, q0, F) */
type DFA struct {
	states       []string
	alphabet     string
	transition   map[string]transition
	initialState string
	finalStates  []string
}

type transition map[string]string

func (d *DFA) accept(in string) bool {
	s := d.initialState

	for _, c := range in {
		s = d.move(s, string(c))
	}

	return contains[string](d.finalStates, s)
}

func (d *DFA) move(s string, c string) (newState string) {
	trans, ok := d.transition[s]
	if !ok {
		log.Fatalf("DFA doenst have transition the state %s", s)
	}

	newState, ok = trans[c]
	if !ok {
		log.Fatalf("DFA doenst have transition for %s in the state %s", s, s)
	}

	return
}

func contains[T comparable](arr []T, s T) bool {
	for _, v := range arr {
		if s == v {
			return true
		}
	}

	return false
}

func main() {
	/* (a|b)*abb */
	dfa := &DFA{
		initialState: "Q0",
		alphabet:     "ab",
		finalStates:  []string{"Q3"},
		states:       []string{"Q0", "Q1", "Q2", "Q3"},
		transition: map[string]transition{
			"Q0": {
				"b": "Q0",
				"a": "Q1",
			},
			"Q1": {
				"b": "Q2",
				"a": "Q1",
			},
			"Q2": {
				"b": "Q3",
				"a": "Q1",
			},
			"Q3": {
				"b": "Q0",
				"a": "Q1",
			},
		},
	}

	in := "babb"
	if dfa.accept(in) {
		fmt.Printf("in = %s accepted\n", in)
	} else {
		fmt.Printf("in = %s not accepted\n", in)
	}
}
