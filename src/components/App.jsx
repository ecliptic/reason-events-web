/***
 * The App component contains all the behind the scenes gadgetry and logic
 * that makes the app tick. Things like "providers" for redux and apollo,
 * the <head> meta data and links, and certain event listeners.
 *
 * A good rule of thumb is, if it's not presentational, but it's functional,
 * and the whole app uses it... it should probably live here.
 */
import 'babel-polyfill'

import React, {Fragment} from 'react'
import Helmet from 'react-helmet'
import {Provider} from 'react-redux'
import {ApolloProvider} from 'react-apollo'

import ApiClient from 'clients/ApiClient.bs'
import {store} from 'state/Store.bs'

const client = ApiClient.client

/***
 * Presentation
 */
const App = ({children, meta}) => {
  return (
    <Fragment>
      <Helmet>
        <html lang="en" />
        <title itemProp="name" lang="en">
          {meta.title}
        </title>

        {/** Metadata */}
        <meta charSet="utf-8" />
        <meta httpEquiv="x-ua-compatible" content="ie=edge" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />

        <meta name="description" content={meta.description} />
        <meta name="author" content={meta.author} />

        {/** Links */}
        <link rel="canonical" href={meta.siteUrl} />
      </Helmet>
      <ApolloProvider client={client}>
        <Provider store={store}><Fragment>{children}</Fragment></Provider>
      </ApolloProvider>
    </Fragment>
  )
}

export default App
