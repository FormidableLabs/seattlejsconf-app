let getUniqueDates data =>
  List.map (fun a => String.sub a##start 0 10) (Array.to_list data) |> List.sort_uniq compare |> Array.of_list;

let getScheduleForDate data date =>
  List.filter (fun a => String.sub a##start 0 10 === date) (Array.to_list data) |> Array.of_list;

let getIndexFromData data =>
  switch data {
  | None => 0
  | Some d => Array.length (getScheduleForDate d (getUniqueDates d).(0)) + 2
  };
