let getItemDate = (item: Item.t) => String.sub(item.start, 0, 10);

let getUniqueDates = (schedule) => List.map(getItemDate, schedule) |> List.sort_uniq(compare);

let getScheduleForDate = (schedule, date) =>
  List.filter((item) => getItemDate(item) === date, schedule);

let getIndexFromSchedule = (schedule) =>
  switch (getUniqueDates(schedule)) {
  | [firstDate, ..._] => List.length(getScheduleForDate(schedule, firstDate)) + 2
  | [] => 2
  };
