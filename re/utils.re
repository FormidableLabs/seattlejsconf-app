let getUniqueDates data =>
  List.map (fun a => String.sub a.Item.start 0 10) data |> List.sort_uniq compare;

let getScheduleForDate data date =>
  List.filter (fun a => String.sub a.Item.start 0 10 === date) data;

let getIndexFromData data =>
  switch data {
  | None => 0
  | Some d => List.length (getScheduleForDate d (List.hd (getUniqueDates d))) + 2
  };