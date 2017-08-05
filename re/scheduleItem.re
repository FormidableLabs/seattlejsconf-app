open ReactNative;

type item =
  Js.t {
    .
    id : string,
    start : string,
    talk :
      Js.null_undefined (
        Js.t {
          .
          title : string,
          description : string,
          speakers :
            Js.Array.t (
              Js.t {. id : string, name : string, bio : string, photo : Js.t {. secret : string}}
            )
        }
      ),
    title : string
  };

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

let make item::(item: item) _children => {
  ...component,
  render: fun _self =>
    <View style=styles##item>
      <View style=styles##row>
        <View style=styles##titleWrap> <ScheduleTitle title=item##title /> </View>
      </View>
      <ScheduleTime start=item##start />
    </View>
};
