# Reason Events - Web

A Gatsby hybrid site generator based on React.

For an overview of the project structure please refer to the [Gatsby documentation - Building with Components](https://www.gatsbyjs.org/docs/building-with-components/)

Some components use [ReasonReact](https://github.com/reasonml/reason-react), a functional interface to React powered by [ReasonML](https://reasonml.github.io/).

## Architecture

* Static site with dynamic build process - Gatsby uses Server Side Rendering (SSR) to generate the static HTML during the production build process.
* Trailmap API - persists user accounts, donation payment methods, referral links, events and rsvps, and peaks and challenges.
* GraphQL communication - 2 separate usages - used to retrieve Gatsby build data during the build process, and to speak to the Trailmap API. The build process usage is powered by a Gatsby global `graphql` tag, and the Trailmap usage is powered by Apollo Client.
* Authentication - we use Auth0 to manage authentication and authorization. An `id_token` and `access_token` are generated through Auth0's libraries and the Trailmap API is called to verify the credentials.

## Installation

Install dependencies with [Yarn](http://yarnpkg.com):

    $ yarn

## Local Development

Run the dev server:

    $ yarn dev

Run the BuckleScript compiler for ReasonML:

    $ yarn build.re.watch

Run a production build:

    $ yarn build
