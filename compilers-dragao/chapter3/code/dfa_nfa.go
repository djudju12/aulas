package main

/*
	CONSTRUÇÃO DE UM DFA SEGUNDO O ALGORITMO 3.18 - PAGINA 96
*/

import (
	"fmt"
	"log"
	"os"
)

/* (Q, Σ, δ, q0, F) */
type DFA struct {
	states       []int
	alphabet     []string
	transition   map[int]transition
	initialState int
	finalStates  []int
}

type transition map[string]int

func (d *DFA) accept(in string) bool {
	s := d.initialState

	for _, c := range in {
		s = d.move(s, string(c))
	}

	return contains[int](d.finalStates, s)
}

func (d *DFA) move(s int, c string) (newState int) {
	trans, ok := d.transition[s]
	if !ok {
		log.Fatalf("DFA doenst have transition the state %d", s)
	}

	newState, ok = trans[c]
	if !ok {
		log.Fatalf("DFA doenst have transition for %d in the state %d", s, s)
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
	alphabet     []string
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
	n.oldStates = append(n.oldStates, n.newStates...)

	var s int
	for _, c := range in {
		for range n.oldStates {
			n.oldStates, s = pop(n.oldStates)
			for _, t := range n.transition[s] {
				if t.c == string(c) && !n.alreadyOn[t.s] {
					n.addState(t.s)
				}
			}
		}

		for range n.newStates {
			n.newStates, s = pop(n.newStates)
			n.oldStates = push(n.oldStates, s)
			n.alreadyOn[s] = false
		}
	}

	return len(intersection(n.oldStates, n.finalStates)) != 0
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

type Dtran struct {
	dstates []int
	trans   transition
}

func newDtran(s []int) Dtran {
	return Dtran{
		trans:   make(transition),
		dstates: s,
	}
}

func (n *NFA) toDFA() DFA {
	var dfa DFA
	dfa.alphabet = n.alphabet
	dtran := make([]Dtran, 0)
	dtran = append(dtran, newDtran(n.closure([]int{n.initialState})))

	notMarkeds := []int{0}

	var index int
	for len(notMarkeds) > 0 {
		index = notMarkeds[0]
		notMarkeds = notMarkeds[1:]
		for _, c := range dfa.alphabet {
			u := n.closure(n.move(dtran[index].dstates, string(c)))
			new := true
			state := 0
			for i, entry := range dtran {
				state = i
				if arrEqual(entry.dstates, u) {
					new = false
					break
				}
			}

			if new {
				dtran = append(dtran, newDtran(u))
				state = len(dtran) - 1
				notMarkeds = append(notMarkeds, state)

				if len(intersection(u, n.finalStates)) != 0 {
					dfa.finalStates = append(dfa.finalStates, state)
				}
			}

			dtran[index].trans[string(c)] = state
		}
	}

	dfa.transition = make(map[int]transition)
	for i, t := range dtran {
		dfa.states = append(dfa.states, i)
		dfa.transition[i] = t.trans
	}

	dfa.initialState = 0

	return dfa
}

func arrEqual(arr []int, arr2 []int) bool {
	if len(arr) != len(arr2) {
		return false
	}
	for i := range arr {
		if arr[i] != arr2[i] {
			return false
		}
	}

	return true
}

func main2() {
	// nfa := &NFA{
	// 	initialState: 0,
	// 	alphabet:     "ab",
	// 	finalStates:  []int{10},
	// 	states:       []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
	// 	alreadyOn:    make([]bool, 11),
	// 	transition: map[int][]NFATransition{
	// 		0: {
	// 			{EWORD, 1},
	// 			{EWORD, 7},
	// 		},
	// 		1: {
	// 			{EWORD, 2},
	// 			{EWORD, 4},
	// 		},
	// 		2: {
	// 			{"a", 3},
	// 		},
	// 		3: {
	// 			{EWORD, 6},
	// 		},
	// 		4: {
	// 			{"b", 5},
	// 		},
	// 		5: {
	// 			{EWORD, 6},
	// 		},
	// 		6: {
	// 			{EWORD, 7},
	// 			{EWORD, 1},
	// 		},
	// 		7: {
	// 			{"a", 8},
	// 		},
	// 		8: {
	// 			{"b", 9},
	// 		},
	// 		9: {
	// 			{"b", 10},
	// 		},
	// 	},
	// }

	/* 3.26 */
	// nfa := &NFA{
	// 	initialState: 0,
	// 	alphabet:     "ab",
	// 	finalStates:  []int{2, 4},
	// 	states:       []int{0, 1, 2, 3, 4},
	// 	transition: map[int][]NFATransition{
	// 		0: {
	// 			{EWORD, 1},
	// 			{EWORD, 3},
	// 		},
	// 		1: {
	// 			{"a", 2},
	// 		},
	// 		2: {
	// 			{"a", 2},
	// 		},
	// 		3: {
	// 			{"b", 4},
	// 		},
	// 		4: {
	// 			{"b", 4},
	// 		},
	// 	},
	// }
	// in := "ababababa"

	/* 3.29 */
	// nfa := &NFA{
	// 	initialState: 0,
	// 	alphabet:     "ab",
	// 	finalStates:  []int{3},
	// 	states:       []int{0, 1, 2, 3},
	// 	transition: map[int][]NFATransition{
	// 		0: {
	// 			{"a", 1},
	// 			{"b", 0},
	// 		},
	// 		1: {
	// 			{"a", 1},
	// 			{"b", 2},
	// 		},
	// 		2: {
	// 			{"a", 1},
	// 			{"b", 3},
	// 		},
	// 		3: {
	// 			{"a", 1},
	// 			{"a", 0},
	// 		},
	// 	},
	// }
	// in := "ababababbb"

	/* 3.30 */
	// nfa := &NFA{
	// 	initialState: 0,
	// 	alphabet:     "ab",
	// 	finalStates:  []int{3},
	// 	states:       []int{0, 1, 2, 3},
	// 	alreadyOn:    make([]bool, 4),
	// 	transition: map[int][]NFATransition{
	// 		0: {
	// 			{"a", 1},
	// 			{EWORD, 3},
	// 		},
	// 		1: {
	// 			{EWORD, 0},
	// 			{"b", 2},
	// 		},
	// 		2: {
	// 			{EWORD, 1},
	// 			{"b", 3},
	// 		},
	// 		3: {
	// 			{"a", 0},
	// 			{EWORD, 2},
	// 		},
	// 	},
	// }
	// in := "ababababbb"

	// dfa := nfa.toDFA()
	// fmt.Printf("%+v\n", dfa)
	// if dfa.accept(in) {
	// 	fmt.Printf("in = %s accepted\n", in)
	// } else {
	// 	fmt.Printf("in = %s not accepted\n", in)
	// }

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

func main() {
	testCases := []struct {
		pattern string
		match   string
	}{
		{
			pattern: "(a|b)*",
			match:   "aabb",
		},
		{
			pattern: "(a*|b*)*",
			match:   "aaabbb",
		},
		{
			pattern: "(ab*)*",
			match:   "abbbabbb",
		},
		{
			pattern: "(a|b)*abb(a|b)*",
			match:   "abaabbabab",
		},
	}

	for _, tc := range testCases {
		nfa := newFromRegex(tc.pattern)
		dfa := nfa.toDFA()

		if !dfa.accept(tc.match) {
			fmt.Printf("tc: %+v\n", tc)
			fmt.Printf("nfa: %+v\n", nfa)
			fmt.Printf("dfa: %+v\n", dfa)
			os.Exit(1)
		} else {
			fmt.Printf("ok: %s\n", tc.pattern)
		}
	}

}

type RegexTranslator struct {
	pattern string
	nfa     *NFA
}

var (
	lookahead  int
	stateCount int
)

func newFromRegex(pattern string) *NFA {
	rgx := &RegexTranslator{
		pattern: pattern,
	}

	lookahead = 0
	stateCount = 0

	rgx.translate()
	rgx.nfa.alreadyOn = make([]bool, len(rgx.nfa.states))
	return rgx.nfa
}

func (rgx *RegexTranslator) translate() {
	rgx.expr()
	rgx.optExpr()
}

func (rgx *RegexTranslator) optExpr() {
	c, ok := rgx.head()
	if !ok {
		return
	}

	if c == ")" {
		return
	}

	if c == "|" {
		rgx.match("|")
		rgx.union()
		rgx.optExpr()
		return
	}

	if c == "*" {
		rgx.match("*")
		rgx.star()
		rgx.optExpr()
		return
	}

	tempTranslator := &RegexTranslator{
		pattern: rgx.pattern,
	}

	tempTranslator.expr()
	tempTranslator.optExpr()
	concNFA := concate(*rgx.nfa, *tempTranslator.nfa)
	rgx.nfa = &concNFA
}

func (rgx *RegexTranslator) expr() {
	c, ok := rgx.head()
	if !ok {
		panic("trying to call lookahead in the end of the pattern")
	}

	switch c {
	case "(":
		rgx.match("(")
		rgx.expr()
		rgx.optExpr()
		rgx.match(")")
	default:
		rgx.character()
		rgx.optExpr()
	}
}

func (rgx *RegexTranslator) character() {
	c, ok := rgx.head()
	if !ok {
		panic("trying to call lookahead in the end of the pattern")
	}

	rgx.match(c)

	initialState := stateCount
	stateCount++

	finalState := stateCount
	stateCount++

	nfa := NFA{
		initialState: initialState,
		finalStates:  []int{finalState},
		states:       []int{initialState, finalState},
		alphabet:     []string{c},
		transition: map[int][]NFATransition{
			initialState: {
				{c, finalState},
			},
		},
	}

	if rgx.nfa == nil {
		rgx.nfa = &nfa
	} else {
		concNFA := concate(*rgx.nfa, nfa)
		rgx.nfa = &concNFA
	}
}

func (rgx *RegexTranslator) match(c string) {
	if string(rgx.pattern[lookahead]) != c {
		log.Fatalf("%c != %s", rgx.pattern[lookahead], c)
	}

	lookahead++
}

func (rgx *RegexTranslator) head() (string, bool) {
	if lookahead >= len(rgx.pattern) {
		return "", false
	}

	return string(rgx.pattern[lookahead]), true
}

func (rgx *RegexTranslator) union() {
	tempTranslator := &RegexTranslator{
		pattern: rgx.pattern,
	}

	tempTranslator.expr()
	rgx.nfa.states = append(rgx.nfa.states, tempTranslator.nfa.states...)

	newInitialState := stateCount
	stateCount++

	newFinalState := stateCount
	stateCount++

	rgx.nfa.transition[newInitialState] = []NFATransition{
		{EWORD, rgx.nfa.initialState},
		{EWORD, tempTranslator.nfa.initialState},
	}

	rgx.nfa.transition[rgx.nfa.finalStates[0]] = append(rgx.nfa.transition[rgx.nfa.finalStates[0]],
		NFATransition{EWORD, newFinalState})

	tempTranslator.nfa.transition[tempTranslator.nfa.finalStates[0]] = append(
		tempTranslator.nfa.transition[tempTranslator.nfa.finalStates[0]],
		NFATransition{EWORD, newFinalState})

	for k, v := range tempTranslator.nfa.transition {
		rgx.nfa.transition[k] = v
	}

	rgx.nfa.initialState = newInitialState
	rgx.nfa.finalStates = []int{newFinalState}

	rgx.nfa.states = append(rgx.nfa.states, newInitialState, newFinalState)

	rgx.nfa.alphabet = union[string](rgx.nfa.alphabet, tempTranslator.nfa.alphabet)
}

func (rgx *RegexTranslator) star() {
	newInitialState := stateCount
	stateCount++

	newFinalState := stateCount
	stateCount++

	rgx.nfa.transition[newInitialState] = []NFATransition{
		{EWORD, rgx.nfa.initialState},
		{EWORD, newFinalState},
	}

	rgx.nfa.transition[rgx.nfa.finalStates[0]] = append(rgx.nfa.transition[rgx.nfa.finalStates[0]],
		NFATransition{EWORD, rgx.nfa.initialState},
		NFATransition{EWORD, newFinalState},
	)

	rgx.nfa.finalStates = []int{newFinalState}
	rgx.nfa.initialState = newInitialState
	rgx.nfa.states = append(rgx.nfa.states, newInitialState, newFinalState)
}

func concate(nfa1 NFA, nfa2 NFA) NFA {
	nfa1.transition[nfa1.finalStates[0]] = nfa2.transition[nfa2.initialState]
	for k, v := range nfa2.transition {
		if k != nfa2.initialState {
			nfa1.transition[k] = v
		}
	}

	return NFA{
		initialState: nfa1.initialState,
		finalStates:  nfa2.finalStates,
		states:       union(nfa1.states, nfa2.states),
		transition:   nfa1.transition,
		alphabet:     union(nfa1.alphabet, nfa2.alphabet),
	}
}

func union[T comparable](arr1 []T, arr2 []T) []T {
	result := arr1[:]

	for _, i := range arr2 {
		if !contains[T](result, i) {
			result = append(result, i)
		}
	}

	return result
}
