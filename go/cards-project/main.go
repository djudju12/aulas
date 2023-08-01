package main

import "fmt"

func main() {
	card := []string{"Ace of Diamonds", newCard()}
	fmt.Println(card)
}

func newCard() string {
	return "Five of Diamonds"
}
