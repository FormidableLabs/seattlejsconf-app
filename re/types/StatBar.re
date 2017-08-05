type statBar = Js.t {. currentHeight : int};

external constants : statBar = "StatusBar" [@@bs.module "react-native"];
