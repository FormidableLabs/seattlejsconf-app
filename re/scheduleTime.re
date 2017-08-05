open ReactNative;

let component = ReasonReact.statelessComponent "ScheduleTime";

let styles =
  StyleSheet.create
    Style.(
      {
        "timeWrapper": style [paddingLeft 10., paddingBottom 10., marginTop (-5.)],
        "time": style [fontFamily "open-sans-bold", fontSize 12., color "white"]
      }
    );

let make ::start _children => {
  ...component,
  render: fun _self =>
    <View style=styles##timeWrapper>
      <Text style=styles##time>
        (
          ReasonReact.stringToElement
            Moment.(moment start |> Moment.utcOffset "-04:00" |> Moment.format "hh:mm a")
        )
      </Text>
    </View>
};
