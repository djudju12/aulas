include .envrc

.PHONY: confirm
confirm:
	@echo -n 'Are you sure? [y/N]' && read ans && [ $${ans:-N} = y  ]

.PHONY: run/api
run/api:
	go run ./cmd/api -db-dsn=${GREENLIGHT_DB_DSN} -smtp-username=${SMTP_USERNAME} -smtp-password=${SMTP_PASSWORD}

.PHONY: db/psql
db/psql:
	psql ${GREENLIGHT_DB_DSN}

.PHONY: db/migration/new
db/migration/new:
	@echo 'Creating migration files for ${name}...'
	migrate create -seq -ext=.sql -dir=./migrations ${name}

.PHONY: db/migrations/up
db/migrations/up: confirm
	@echo 'Running up migrations...'
	migrate -path ./migrations -database ${GREENLIGHT_DB_DSN} up

.PHONY: audit
audit: vendor
	@echo 'Formatting code...'
	go fmt ./...
	@echo 'Vetting code...'
	go vet ./...
	staticcheck ./...
	@echo 'Running tests...'
	go test -race -vet=off ./...

.PHONY: vendor
vendor:
	@echo 'Tidying and verifying module depencecies...'
	go mod tidy
	go mod verify
	@echo 'Vendoring dependencies...'
	go mod vendor
