package main

import "fmt"

type Symbol string

type Env struct {
	table map[string]Symbol
	prev  *Env
}

func main() {
	top := &Env{
		table: make(map[string]Symbol),
	}

	fmt.Printf("first block top = %+v\n", top)

	top.put("teste", Symbol("teste1"))
	top.put("x", "10")
	fmt.Printf("expected = %s founded = %s\n", "teste1", top.get("teste"))
	{
		saved := top
		top = NewEnv(*top)
		fmt.Printf("second block top = %+v\n", top)
		top.put("teste", Symbol("teste2"))
		fmt.Printf("expected = %s founded = %s\n", "teste2", top.get("teste"))
		fmt.Printf("expected = %s founded = %s\n", "10", top.get("x"))
		top = saved
	}

	fmt.Printf("after exiting from second block top = %+v\n", top)

}

func NewEnv(prev Env) *Env {
	return &Env{
		table: make(map[string]Symbol),
		prev:  &prev,
	}
}

func (e *Env) put(s string, sym Symbol) {
	e.table[s] = sym
}

func (e *Env) get(s string) Symbol {
	for env := e; env != nil; env = e.prev {
		if sym, exists := env.table[s]; exists {
			return sym
		}
	}

	return ""
}
