// @flow
import React from 'react'

let stylesStr
if (process.env.NODE_ENV === 'production') {
  try {
    stylesStr = require('!raw-loader!../public/styles.css') // eslint-disable-line import/no-webpack-loader-syntax
  } catch (e) {
    console.log(e) // eslint-disable-line no-console
  }
}

module.exports = class HTML extends React.Component<*, *> {
  render () {
    let css
    if (process.env.NODE_ENV === 'production') {
      css = (
        <style
          id="gatsby-inlined-css"
          dangerouslySetInnerHTML={{__html: stylesStr}}
        />
      )
    }
    return (
      <html {...this.props.htmlAttributes}>
        <head>
          {this.props.headComponents}
          {css}
          <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons" />
          <link rel="stylesheet" href="https://unpkg.com/material-components-web@0.29.0/dist/material-components-web.min.css" />
        </head>
        <body {...this.props.bodyAttributes}>
          {this.props.preBodyComponents}
          <div
            key={'body'}
            id="___gatsby"
            dangerouslySetInnerHTML={{__html: this.props.body}}
          />
          {this.props.postBodyComponents}
        </body>
      </html>
    )
  }
}
