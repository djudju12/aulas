package data

import (
	"fmt"

	"github.com/djudju12/greenlight/internal/validator"
)

type Filters struct {
	Page         int
	PageSize     int
	Sort         string
	SortSafelist []string
}

var (
	minPageSize = 0
	maxPageSize = 10_000_000
	minPage     = 0
	maxPage     = 100
)

func ValidateFilter(v *validator.Validator, f Filters) {
	v.Check(f.Page > minPage, "page", fmt.Sprintf("must be greater than %d", minPage))
	v.Check(f.Page <= maxPage, "page", fmt.Sprintf("must be a maximum of %d", maxPageSize))
	v.Check(f.PageSize > minPageSize, "page_size", fmt.Sprintf("must be greater than %d", minPageSize))
	v.Check(f.PageSize <= maxPageSize, "page_size", fmt.Sprintf("must be a maximum of %d", maxPageSize))

	v.Check(validator.In(f.Sort, f.SortSafelist...), "sort", "invalid sort value")
}
