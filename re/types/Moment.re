module Moment = {
  type t;
  [@bs.send.pipe : t] external format : string => string = "";
  [@bs.send.pipe : t] external utcOffset : string => t = "";
};

[@bs.module] external _moment : string => Moment.t = "moment";

let moment = (value) => _moment(value);
