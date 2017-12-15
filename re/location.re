open ReactNative;

/* Variables */
let windowWidth = Dimensions.get(`window)##width;

let initialRegion = {
  "latitude": 47.651857,
  "longitude": (-122.3552919),
  "latitudeDelta": 0.001,
  "longitudeDelta": 0.001
};

let coordinate = {"latitude": 47.651857, "longitude": (-122.3552919)};

let iosDirections = "http://maps.apple.com/?daddr=47.651857,-122.3552919";

let androidDirections = "http://maps.google.com/maps?daddr=47.651857,-122.3552919";

/* Methods */
let getDirections = () =>
  if (Platform.os === Platform.IOS) {
    Link.openURL(iosDirections)
  } else {
    Link.openURL(androidDirections)
  };

/* Component */
let component = ReasonReact.statelessComponent("Location");

/* Styles */
let styles =
  StyleSheet.create(
    Style.(
      {
        "container": style([flex(1.), backgroundColor("rgb(54, 97, 115)")]),
        "contentContainer":
          style([
            alignItems(`stretch),
            justifyContent(`center),
            paddingTop(
              Platform.os === Platform.IOS ? 20. : float_of_int(StatBar.constants##currentHeight)
            )
          ]),
        "mapview":
          style([
            width(float_of_int(windowWidth)),
            height(float_of_int(windowWidth) *. 0.656),
            marginBottom(10.)
          ]),
        "foundry":
          style([
            width(float_of_int(windowWidth) -. 20.),
            height(float_of_int(windowWidth) *. 0.569)
          ]),
        "row": style([flex(1.), flexDirection(`column)]),
        "contentWrapper": style([padding(10.), marginTop(10.)]),
        "text":
          style([
            fontFamily("open-sans"),
            fontSize(18.),
            color("white"),
            textAlign(`center),
            backgroundColor("transparent")
          ]),
        "button":
          style([
            backgroundColor("rgb(140, 170, 29)"),
            padding(10.),
            margin(10.),
            borderRadius(24.),
            flex(0.)
          ]),
        "boldText":
          style([
            fontFamily("open-sans-bold"),
            fontSize(18.),
            color("white"),
            backgroundColor("transparent"),
            marginBottom(20.)
          ]),
        "regularText":
          style([
            fontFamily("open-sans"),
            fontSize(15.),
            color("white"),
            backgroundColor("transparent"),
            marginBottom(20.)
          ])
      }
    )
  );

/* Make */
let make = (_, _children) => {
  ...component,
  render: (_self) =>
    <ScrollView style=styles##container>
      <View style=styles##contentContainer>
        <MapView initialRegion style=styles##mapview>
          <MapView.Marker
            title="Fremont Foundry"
            image=(
              Platform.os === Platform.IOS ?
                Packager.require("../../../static/pin.png") :
                Packager.require("../../../static/pin_small.png")
            )
            coordinate
          />
        </MapView>
        <TouchableOpacity onPress=getDirections>
          <View style=styles##button> <Text style=styles##text value="GET DIRECTIONS" /> </View>
        </TouchableOpacity>
        <View style=styles##contentWrapper>
          <Text style=styles##boldText value="WHEN: AUGUST 10th - 11th 2017" />
          <Text style=styles##boldText value="WHERE: FREMONT FOUNDRY" />
          <Text
            style=styles##regularText
            value="SeattleJS's inaugural annual conference will be located at the beautiful and unique Fremont Foundry, located at 154 North 35th Street, Seattle, WA 98103."
          />
          <Image
            source=Image.(Required(Packager.require("../../../static/foundry.jpg")))
            style=styles##foundry
            resizeMode=`cover
          />
        </View>
      </View>
    </ScrollView>
};

/* JS Export */
let jsComponent = ReasonReact.wrapReasonForJs(~component, (_props) => make((), [||]));