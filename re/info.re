open ReactNative;

/* Variables */
let windowWidth = Dimensions.get(`window)##width;

/* Methods */
/* Component */
let component = ReasonReact.statelessComponent("Info");

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
        <SponsorTitle value="RESOURCES" />
        <TouchableOpacity
          onPress=(
            (_) =>
              Link.openURL("https://github.com/seattlejs/seattlejs/blob/master/code-of-conduct.md")
          )>
          <View style=styles##button> <Text style=styles##text value="CODE OF CONDUCT" /> </View>
        </TouchableOpacity>
        <TouchableOpacity onPress=((_) => Link.openURL("mailto:conference@seattlejs.com"))>
          <View style=styles##button> <Text style=styles##text value="CONTACT US" /> </View>
        </TouchableOpacity>
        <SponsorTitle value="PRESENTING SPONSOR" />
        <SponsorCard
          logo=Image.(
                 Required(Packager.require("../../../static/sponsors/formidable-logo-black.png"))
               )
          url="http://www.formidable.com"
          description="Formidable is a Seattle-based consultancy and open-source shop, with an emphasis on Node.js and React.js. For our clients, Formidable is the choice when big or complex software projects need expert help. For us, quality is paramount in everything we do. Quality software scales, performs better, and leads to more happiness and an improved bottom line. We approach each project with a long term view, with sustainability and maintainability at the core of our decisions. We've helped household names construct some of the most visited sites and apps on earth."
        />
        <SponsorTitle value="DIAMOND SPONSORS" />
        <SponsorCard
          url="https://msdn.microsoft.com/en-us"
          logo=Image.(Required(Packager.require("../../../static/sponsors/microsoft.png")))
          description="Our mission is to empower every person and organization on the planet to achieve more. That's what inspires us, drives our work and pushes us to challenge the status quo every day. At Microsoft, we also work to empower our employees, so they can achieve more. We believe we should each find meaning in our work and we ensure employees have the freedom and the reach to help make a difference in the world. We know where we're going as a company and how we'll get there. We are committed to reinvent productivity and business processes, build the intelligent cloud platform and create more personal computing."
        />
        <SponsorTitle value="PLATINUM SPONSORS" />
        <SponsorCard
          url="https://www.amazon.jobs/en/business_categories/alexa"
          logo=Image.(Required(Packager.require("../../../static/sponsors/alexaLogo.png")))
          description="Alexa is Amazon's voice service and the brain behind millions of devices, including Amazon Echo. We believe voice is the future of technology interaction, providing a natural interface to make complex things simple. Are you passionate about building the world of tomorrow? If so, join us!"
        />
        <SponsorTitle value="GOLD SPONSORS" />
        <SponsorCard
          url="http://www.imdb.com/"
          logo=Image.(Required(Packager.require("../../../static/sponsors/imdb.png")))
          description="IMDb is the #1 movie website in the world with a combined web and mobile audience of more than 250 million unique monthly visitors."
        />
        <SponsorTitle value="SILVER SPONSORS" />
        <SponsorCard
          url="https://www.zillow.com/"
          logo=Image.(Required(Packager.require("../../../static/sponsors/zillow.png")))
        />
        <SponsorCard
          url="https://www.galvanize.com/seattle/web-development"
          logo=Image.(Required(Packager.require("../../../static/sponsors/galvanize.png")))
        />
        <SponsorCard
          url="https://www.appsheet.com/"
          logo=Image.(Required(Packager.require("../../../static/sponsors/appsheet.png")))
        />
        <SponsorCard
          url="https://www.godaddy.com/"
          logo=Image.(Required(Packager.require("../../../static/sponsors/godaddy.png")))
        />
        <SponsorTitle value="COMMUNITY SPONSORS" />
        <SponsorCard
          url="https://www.npmjs.com/"
          logo=Image.(Required(Packager.require("../../../static/sponsors/npm-logo.png")))
        />
        <SponsorCard
          url="https://www.sitepen.com/"
          logo=Image.(Required(Packager.require("../../../static/sponsors/sitepen.png")))
        />
        <SponsorCard
          url="https://www.indeed.jobs/"
          logo=Image.(Required(Packager.require("../../../static/sponsors/Indeed.png")))
        />
        <SponsorCard
          url="https://www.opendoor.com/"
          logo=Image.(Required(Packager.require("../../../static/sponsors/Opendoor.png")))
        />
        <SponsorCard
          url="http://shecodesnow.com/"
          logo=Image.(Required(Packager.require("../../../static/sponsors/she-codes-now.png")))
        />
        <SponsorCard
          url="https://sendgrid.com/"
          logo=Image.(Required(Packager.require("../../../static/sponsors/sendgrid.png")))
        />
      </View>
    </ScrollView>
};

/* JS Export */
let jsComponent = ReasonReact.wrapReasonForJs(~component, (_props) => make((), [||]));