let query =
  GraphQLTag.gql {|
  query allSchedules {
    allSchedules {
      id
      start
      talk {
        title
        description
        speakers {
          id
          name
          bio
          photo {
            secret
          }
        }
      }
      title
    }
  }
|};


type speakers =
  Js.Array.t (Js.t {. id : string, name : string, bio : string, photo : Js.t {. secret : string}});

type talk = Js.t {. title : string, description : string, speakers : speakers};

type t = Js.t {. id : string, start : string, talk : Js.null_undefined talk, title : string};