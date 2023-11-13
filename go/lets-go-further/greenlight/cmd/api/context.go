package main

import (
	"context"
	"net/http"

	"github.com/djudju12/greenlight/internal/data"
)

type contextKey string

const userContextKey = contextKey("user")

func (app *application) contenxtSetUser(r *http.Request, user *data.User) *http.Request {
	ctx := context.WithValue(r.Context(), userContextKey, user)
	return r.WithContext(ctx)
}

func (app *application) contenxtGetUser(r *http.Request) *data.User {
	user, ok := r.Context().Value(userContextKey).(*data.User)
	if !ok {
		panic("missing user value in request")
	}

	return user
}
