module Moment = {
  type t;
  external format : string => string = "" [@@bs.send.pipe : t];
  external utcOffset : string => t = "" [@@bs.send.pipe : t];
};

external _moment : string => Moment.t = "moment" [@@bs.module];

let moment value => _moment value;
