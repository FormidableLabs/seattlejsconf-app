open ReactNative;

let styles =
  StyleSheet.create
    Style.(
      {
        "item":
          style [
            flex 1.,
            marginHorizontal 10.,
            marginTop 10.,
            borderWidth 1.,
            borderColor "transparent"
          ],
        "row": style [flexDirection `row],
        "titleWrap": style [flex 1., padding 10.]
      }
    );

let component = ReasonReact.statelessComponent "ScheduleItem";

let make item::(item: Item.t) _children => {
  ...component,
  render: fun _self =>
    <View style=styles##item>
      <View style=styles##row>
        <View style=styles##titleWrap> <ScheduleTitle title=item##title /> </View>
      </View>
      <ScheduleTime start=item##start />
    </View>
};