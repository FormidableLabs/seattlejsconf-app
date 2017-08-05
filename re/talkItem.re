open ReactNative;

type _state = {mutable elementRef: option ReasonReact.reactRef};

let setRef theRef {ReasonReact.state: state} => state.elementRef = Js.Null.to_opt theRef;

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
            backgroundColor "rgb(75, 118, 134)",
            marginHorizontal 10.,
            marginTop 10.,
            borderWidth 1.,
            borderColor "rgb(137, 167, 177)"
          ],
        "row": style [flexDirection `row],
        "titleWrap": style [flex 1., padding 10.]
      }
    );

let component = ReasonReact.statefulComponent "TalkItem";

let make
    item::(item: item)
    ::talk
    index::(index: int)
    modalOpen::(modalOpen: bool)
    selectedIndex::(selectedIndex: int)
    ::onPress
    _children => {
  ...component,
  initialState: fun () => {elementRef: None},
  render: fun self =>
    <TouchableOpacity
      onPress=(
        fun _ =>
          switch self.state.elementRef {
          | None => ()
          | Some r =>
            (ReasonReact.refToJsObj r)##measureInWindow (
              fun x y width height => onPress (x, y, width, height, item, index)
            )
          }
      )>
      <View
        style=Style.(
                concat [
                  styles##item,
                  style [opacity (modalOpen && index === selectedIndex ? 0. : 1.)]
                ]
              )
        ref=(self.handle setRef)>
        <View style=styles##row>
          <View style=styles##titleWrap>
            <ScheduleTitle title=talk##title />
            <SpeakerNames talk />
          </View>
          <SpeakerImages talk />
        </View>
        <ScheduleTime start=item##start />
      </View>
    </TouchableOpacity>
};
