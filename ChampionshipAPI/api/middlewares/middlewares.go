package middlewares

import (
	"ChampionshipAPI/api/auth"
	"ChampionshipAPI/api/models"
	"ChampionshipAPI/api/utils/types"
	"context"
	"log"
	"net/http"
)

// SetMiddlewareLogger displays a info message of the API
// SetMiddlewareLogger отображает информационное сообщение API
func SetMiddlewareLogger(next http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		log.Printf("%s %s%s %s", r.Method, r.Host, r.RequestURI, r.Proto)
		next(w, r)
	}
}

// SetMiddlewareJSON set the application Content-Type
// SetMiddlewareJSON  устанавливает заголовок Content-Type
func SetMiddlewareJSON(next http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		next(w, r)
	}
}

// SetMiddlewareAuthentication authorize an access
// SetMiddlewareAuthentication : авторизация
func SetMiddlewareAuthentication(next http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		token := auth.ExtractToken(w, r)
		if token == nil {
			return
		}
		if token.Valid {
			ctx := context.WithValue(
				r.Context(),
				types.UserKey("user"),
				token.Claims.(*models.Claim).User,
			)
			next(w, r.WithContext(ctx))
		}
	}
}
