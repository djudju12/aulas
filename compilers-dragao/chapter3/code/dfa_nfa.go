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

const EWORD = "&"

/* (Q, Σ, δ, q0, F) */
type NFA struct {
	states       []string
	alphabet     string
	transition   map[string][]NFATransition
	initialState []string
	finalStates  []string
}

type NFATransition struct {
	c string
	s string
}

func (n *NFA) accept(in string) bool {
	s := n.closure(n.initialState)
	for _, c := range in {
		s = n.closure(n.move(s, string(c)))
	}

	return len(intersection(s, n.finalStates)) != 0
}

func (n *NFA) move(states []string, c string) []string {
	var result []string
	for _, s := range states {
		ts := n.transition[s]
		for _, t := range ts {
			if t.c == c && !contains(result, t.s) {
				result = append(result, t.s)
			}
		}
	}

	return result
}

func intersection(arr1 []string, arr2 []string) []string {
	i := []string{}
	for _, value := range arr1 {
		if contains(arr2, value) && !contains(i, value) {
			i = append(i, value)
		}
	}

	return i
}

func (n *NFA) closure(states []string) []string {
	candidates := states[:]
	result := states[:]
	var curr string

	for len(candidates) > 0 {
		candidates, curr = pop(candidates)
		ts := n.transition[curr]
		for _, t := range ts {
			if t.c == EWORD && !contains(result, t.s) {
				result = append(result, t.s)
				candidates = push(candidates, t.s)
			}
		}
	}

	return result
}

func push(s []string, v string) []string {
	return append(s, v)
}

func pop(s []string) ([]string, string) {
	if len(s) == 0 {
		panic("pop on empty stack")
	}

	result := s[len(s)-1]
	s = s[0 : len(s)-1]

	return s, result
}

func main() {
	nfa := &NFA{
		initialState: []string{"Q0"},
		alphabet:     "ab",
		finalStates:  []string{"Q10"},
		states:       []string{"Q0", "Q1", "Q2", "Q3", "Q4", "Q5", "Q6", "Q7", "Q8", "Q9", "Q10"},
		transition: map[string][]NFATransition{
			"Q0": {
				{EWORD, "Q1"},
				{EWORD, "Q7"},
			},
			"Q1": {
				{EWORD, "Q2"},
				{EWORD, "Q4"},
			},
			"Q2": {
				{"a", "Q3"},
			},
			"Q3": {
				{EWORD, "Q6"},
			},
			"Q4": {
				{"b", "Q5"},
			},
			"Q5": {
				{EWORD, "Q6"},
			},
			"Q6": {
				{EWORD, "Q7"},
				{EWORD, "Q1"},
			},
			"Q7": {
				{"a", "Q8"},
			},
			"Q8": {
				{"b", "Q9"},
			},
			"Q9": {
				{"b", "Q10"},
			},
		},
	}

	in := "babb"
	if nfa.accept(in) {
		fmt.Printf("in = %s accepted\n", in)
	} else {
		fmt.Printf("in = %s not accepted\n", in)
	}

	/* (a|b)*abb */
	// dfa := &DFA{
	// 	initialState: "Q0",
	// 	alphabet:     "ab",
	// 	finalStates:  []string{"Q3"},
	// 	states:       []string{"Q0", "Q1", "Q2", "Q3"},
	// 	transition: map[string]transition{
	// 		"Q0": {
	// 			"b": "Q0",
	// 			"a": "Q1",
	// 		},
	// 		"Q1": {
	// 			"b": "Q2",
	// 			"a": "Q1",
	// 		},
	// 		"Q2": {
	// 			"b": "Q3",
	// 			"a": "Q1",
	// 		},
	// 		"Q3": {
	// 			"b": "Q0",
	// 			"a": "Q1",
	// 		},
	// 	},
	// }

	// in := "babb"
	// if dfa.accept(in) {
	// 	fmt.Printf("in = %s accepted\n", in)
	// } else {
	// 	fmt.Printf("in = %s not accepted\n", in)
	// }
}
