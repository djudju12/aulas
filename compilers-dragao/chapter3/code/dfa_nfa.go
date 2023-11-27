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
	states       []int
	alphabet     string
	transition   map[int][]NFATransition
	initialState int
	finalStates  []int

	oldStates []int
	newStates []int
	alreadyOn []bool
}

type NFATransition struct {
	c string
	s int
}

func (n *NFA) addState(s int) {
	n.newStates = push(n.newStates, s)
	n.alreadyOn[s] = true
	for _, t := range n.transition[s] {
		if t.c == EWORD && !n.alreadyOn[t.s] {
			n.addState(t.s)
		}
	}
}

func (n *NFA) accept(in string) bool {
	n.addState(n.initialState)
	for _, s := range n.oldStates {
		for _, t := range n.transition[s] {
			if t.c == "a" && !n.alreadyOn[t.s] {
				n.addState(t.s)
				n.oldStates, _ = pop(n.oldStates)
			}
		}
	}

	for _, s := range n.newStates {
		n.newStates, _ = pop(n.newStates)
		n.oldStates = push(n.oldStates, s)
		n.alreadyOn[s] = false
	}

	fmt.Println(n.newStates)
	return true
}

func (n *NFA) move(states []int, c string) []int {
	var result []int
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

func intersection(arr1 []int, arr2 []int) []int {
	i := []int{}
	for _, value := range arr1 {
		if contains(arr2, value) && !contains(i, value) {
			i = append(i, value)
		}
	}

	return i
}

func (n *NFA) closure(states []int) []int {
	candidates := states[:]
	result := states[:]
	var curr int

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

func push(s []int, v int) []int {
	return append(s, v)
}

func pop(s []int) ([]int, int) {
	if len(s) == 0 {
		panic("pop on empty stack")
	}

	result := s[len(s)-1]
	s = s[0 : len(s)-1]

	return s, result
}

func main() {
	nfa := &NFA{
		initialState: 0,
		alphabet:     "ab",
		finalStates:  []int{10},
		states:       []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
		alreadyOn:    make([]bool, 11),
		transition: map[int][]NFATransition{
			0: {
				{EWORD, 1},
				{EWORD, 7},
			},
			1: {
				{EWORD, 2},
				{EWORD, 4},
			},
			2: {
				{"a", 3},
			},
			3: {
				{EWORD, 6},
			},
			4: {
				{"b", 5},
			},
			5: {
				{EWORD, 6},
			},
			6: {
				{EWORD, 7},
				{EWORD, 1},
			},
			7: {
				{"a", 8},
			},
			8: {
				{"b", 9},
			},
			9: {
				{"b", 10},
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
