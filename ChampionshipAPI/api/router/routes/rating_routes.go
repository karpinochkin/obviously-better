package routes

import (
	"ChampionshipAPI/api/controllers"
	"net/http"
)

var ratingRoutes = []Route{
	Route{
		URI:          "/rating",
		Method:       http.MethodGet,
		Handler:      controllers.GetAllRating,
		AuthRequired: false,
	},
	Route{
		URI:          "/rating",
		Method:       http.MethodPost,
		Handler:      controllers.CreateRatingRow,
		AuthRequired: false,
	},
	Route{
		URI:          "/rating/{id}",
		Method:       http.MethodGet,
		Handler:      controllers.GetRatingRow,
		AuthRequired: false,
	},
	Route{
		URI:          "/rating/{id}",
		Method:       http.MethodPut,
		Handler:      controllers.UpdateRatingRow,
		AuthRequired: true,
	},
	Route{
		URI:          "/rating/{id}",
		Method:       http.MethodDelete,
		Handler:      controllers.DeleteRatingRow,
		AuthRequired: true,
	},
	Route{
		URI:          "/rating/contests/{id}",
		Method:       http.MethodGet,
		Handler:      controllers.GetRatingByContest,
		AuthRequired: false,
	},
}
