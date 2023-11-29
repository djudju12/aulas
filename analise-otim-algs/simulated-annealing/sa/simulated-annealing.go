package sa

import (
	"math"
	"math/rand"
	"strconv"
	"time"
)

var random *rand.Rand

func init() {
	random = rand.New(rand.NewSource(time.Now().UnixNano()))
}

const Epsilon = 2.2204460492503131e-16

type Solver struct {
	Candidates []candidate
	Limiter    float64
}

type candidate struct {
	value float64
	cost  float64
}

type Solution struct {
	candidatesIndex []int
	TotalCost       float64
}

func (solver *Solver) Solve(
	iterMax int,
	alpha float64,
	temp0 float64,
	initialSolution Solution,
) Solution {
	solution := initialSolution
	currSolution := initialSolution
	i := 0
	temp := temp0
	for temp > 1.0e-10 {
		for i < iterMax {
			i++
			tempSolution := solver.generateNeighborSolution(currSolution)
			deltaS := solver.TotalValue(tempSolution) - solver.TotalValue(currSolution)
			if deltaS > 0 {
				currSolution = tempSolution
				if solver.TotalValue(currSolution) > solver.TotalValue(solution) {
					solution = currSolution
				}
			} else {
				x := random.Float64()
				y := math.Pow(Epsilon, (-deltaS / temp))
				if x < y {
					currSolution = tempSolution
				}
			}
		}
		temp = temp * alpha
		i = 0
	}

	return solution
}

func (solver *Solver) GenerateNaiveSolution() Solution {
	var candidates []int
	totalCost := 0.0
	for i, c := range solver.Candidates {
		if c.cost+totalCost <= solver.Limiter {
			totalCost += c.cost
			candidates = append(candidates, i)
		}

		if totalCost == solver.Limiter {
			break
		}
	}

	return Solution{
		candidatesIndex: candidates,
		TotalCost:       totalCost,
	}
}

func (solver *Solver) generateNeighborSolution(s Solution) Solution {
	newSolution := Solution{
		candidatesIndex: make([]int, len(s.candidatesIndex)),
		TotalCost:       s.TotalCost,
	}
	copy(newSolution.candidatesIndex, s.candidatesIndex)

	skip := random.Intn(len(newSolution.candidatesIndex))
	skipCandidate := newSolution.candidatesIndex[skip]

	newSolution.TotalCost -= solver.Candidates[skipCandidate].cost

	newSolution.candidatesIndex = append(
		newSolution.candidatesIndex[:skip],
		newSolution.candidatesIndex[skip+1:]...,
	)

	for i, c := range solver.Candidates {
		if !contains(newSolution.candidatesIndex, i) && i != skipCandidate {
			if newSolution.TotalCost+c.cost <= solver.Limiter {
				newSolution.candidatesIndex = append(newSolution.candidatesIndex, i)
				newSolution.TotalCost += c.cost
			}

			if newSolution.TotalCost == solver.Limiter {
				break
			}

			if newSolution.TotalCost > solver.Limiter {
				panic("wtf")
			}
		}
	}

	return newSolution
}

func contains[T comparable](arr []T, v T) bool {
	for _, i := range arr {
		if i == v {
			return true
		}
	}

	return false
}

func (solver *Solver) TotalValue(s Solution) float64 {
	total := 0.0
	for _, i := range s.candidatesIndex {
		total += solver.Candidates[i].value
	}

	return float64(total)
}

func NewSolver(data []string) *Solver {
	solver := &Solver{}
	size, err := strconv.Atoi(data[0])
	if err != nil {
		panic(err)
	}

	limiter, err := strconv.ParseFloat(data[1], 64)
	if err != nil {
		panic(err)
	}

	solver.Limiter = limiter
	solver.Candidates = make([]candidate, size)

	data = data[2:]

	for i := 0; i < size*2; i += 2 {
		value, err := strconv.ParseFloat(data[i], 64)
		if err != nil {
			panic(err)
		}
		cost, err := strconv.ParseFloat(data[i+1], 64)
		if err != nil {
			panic(err)
		}

		solver.Candidates[i/2] = candidate{value: value, cost: cost}
	}

	return solver
}
