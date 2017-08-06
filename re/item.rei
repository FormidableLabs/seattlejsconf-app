let query: GraphQLTag.definitions;

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

type t_js;

let convert_from_js: t_js => t;