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

module ItemJS = {
  type photo = Js.t {. secret : string};
  type speaker = Js.t {. name : string, bio : string, photo : photo};
  type talk = Js.t {. title : string, description : string, speakers : Js.Array.t speaker};
  type t = Js.t {. id : string, start : string, talk : Js.null_undefined talk, title : string};
};

type speaker = {
  name: string,
  bio: string,
  photo: string
};

type talk = {
  talkTitle: string,
  description: string,
  speakers: array speaker
};

type t = {
  id: string,
  start: string,
  talk: option talk,
  title: string
};

let convert_speaker (s: ItemJS.speaker) => {name: s##name, bio: s##bio, photo: s##photo##secret};

let convert_talk (t: ItemJS.talk) => {
  talkTitle: t##title,
  description: t##description,
  speakers: Array.map convert_speaker t##speakers
};

let convert_from_js (t: ItemJS.t) => {
  id: t##id,
  start: t##start,
  talk:
    switch (Js.Null_undefined.to_opt t##talk) {
    | None => None
    | Some talk_js => Some (convert_talk talk_js)
    },
  title: t##title
};

type t_js = ItemJS.t;