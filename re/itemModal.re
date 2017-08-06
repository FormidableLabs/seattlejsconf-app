open ReactNative;

type _state = {scrollRef: option ReasonReact.reactRef};

let setRef theRef _ => ReasonReact.SilentUpdate {scrollRef: Js.Null.to_opt theRef};

let styles =
  StyleSheet.create
    Style.(
      {
        "item": style [flex 1.],
        "row": style [flexDirection `row],
        "titleWrap": style [flex 1., padding 10.],
        "wrapper":
          style [
            position `relative,
            flex 1.,
            backgroundColor "rgb(75, 118, 134)",
            borderWidth 1.,
            borderColor "rgb(137, 167, 177)"
          ]
      }
    );

let component = ReasonReact.statefulComponent "ItemModal";

let make
    item::{Item.start: start, talk, title}
    ::contentOpacity
    ::backgroundOpacity
    ::expanded
    onClose::(onClose: unit => unit)
    _children => {
  ...component,
  initialState: fun () => {scrollRef: None},
  render: fun self => {
    let fadingContainerStyle value => Style.(style [opacityAnimated value]);
    let contentContainerOpacity = fadingContainerStyle contentOpacity;
    <Animated.View style=Style.(concat [styles##wrapper, fadingContainerStyle backgroundOpacity])>
      <ScrollView style=styles##item ref=(self.update setRef)>
        <View style=styles##row>
          <View style=styles##titleWrap>
            (
              switch talk {
              | None => <ScheduleTitle talkTitle=title />
              | Some {Item.talkTitle: talkTitle} => <ScheduleTitle talkTitle />
              }
            )
            (
              switch talk {
              | None => ReasonReact.nullElement
              | Some talk => <SpeakerNames talk />
              }
            )
          </View>
          (
            switch talk {
            | None => ReasonReact.nullElement
            | Some talk => <SpeakerImages talk />
            }
          )
        </View>
        <ScheduleTime start />
        (
          switch expanded {
          | false => ReasonReact.nullElement
          | true =>
            switch talk {
            | None => ReasonReact.nullElement
            | Some {Item.description: description, speakers} =>
              <Animated.View style=contentContainerOpacity>
                <TalkDescription value=description />
                <SpeakerBio speakers />
              </Animated.View>
            }
          }
        )
      </ScrollView>
      (
        switch expanded {
        | false => ReasonReact.nullElement
        | true =>
          <Animated.View style=contentContainerOpacity>
            <CloseButton
              onPress=(
                fun () => {
                  switch self.state.scrollRef {
                  | None => ()
                  | Some s =>
                    (ReasonReact.refToJsObj s)##scrollTo [%bs.raw "{y: 0, animated: false}"]
                  };
                  onClose ()
                }
              )
            />
          </Animated.View>
        }
      )
    </Animated.View>
  }
};