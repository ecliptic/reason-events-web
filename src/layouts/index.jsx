/**
 * The Layout component is for all the presentational aspects of the app.
 * It's the counterpart to the App component (which handles the non-presentational stuff
 * that the whole app uses.)
 *
 * A good rule of thumb for Layout is, if it's presentational and every page uses it,
 * it should live here.
 */
import React from 'react'

import App from 'components/App'
import Header from 'components/Header'
import Footer from 'components/Footer'

import './reset.css'
import './globals.css'

/***
 * Presentation
 */
class Layout extends React.Component {
  render () {
    const {
      children,
      data,
    } = this.props
    return (
      <App meta={data.site.siteMetadata}>
        <Header />
        {children()}
        <Footer />
      </App>
    )
  }
}

/***
 * Data
 */
/* eslint-disable no-undef */
export const query = graphql`
  query HomepageQuery {
    site {
      id
      siteMetadata {
        title
        author
        description
        siteUrl
      }
    }
  }
`
/* eslint-enable no-undef */

export default Layout
