package routes

import (
	"ChampionshipAPI/api/controllers"
	"net/http"
)

var contestRoutes = []Route{
	Route{
		URI:          "/contests",
		Method:       http.MethodGet,
		Handler:      controllers.GetContests,
		AuthRequired: false,
	},
	Route{
		URI:          "/contests/{id}/quantity/{value}",
		Method:       http.MethodGet,
		Handler:      controllers.GetContestsByRange,
		AuthRequired: false,
	},
	Route{
		URI:          "/contests",
		Method:       http.MethodPost,
		Handler:      controllers.CreateContest,
		AuthRequired: true,
	},
	Route{
		URI:          "/contests/{id}",
		Method:       http.MethodGet,
		Handler:      controllers.GetContest,
		AuthRequired: false,
	},
	Route{
		URI:          "/contests/{id}",
		Method:       http.MethodPut,
		Handler:      controllers.UpdateContest,
		AuthRequired: true,
	},
	Route{
		URI:          "/contests/{id}",
		Method:       http.MethodDelete,
		Handler:      controllers.DeleteContest,
		AuthRequired: true,
	},
	Route{
		URI:          "/contests/{id}/count/membertypes",
		Method:       http.MethodGet,
		Handler:      controllers.CountMemberTypesInContest,
		AuthRequired: false,
	},
	Route{
		URI:          "/count/contests",
		Method:       http.MethodGet,
		Handler:      controllers.CountContests,
		AuthRequired: false,
	},
	Route{
		URI:          "/contests/{id}/membertypes",
		Method:       http.MethodGet,
		Handler:      controllers.GetMemberTypesForContest,
		AuthRequired: false,
	},
	Route{
		URI:          "/contests/{id}/members",
		Method:       http.MethodGet,
		Handler:      controllers.CountOfMembersForContest,
		AuthRequired: false,
	},
	Route{
		URI:          "/contests/{id}/random/members",
		Method:       http.MethodPost,
		Handler:      controllers.GetRandomMembersForContest,
		AuthRequired: false,
	},
}
