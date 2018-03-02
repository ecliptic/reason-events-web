import React from 'react'
import {Toolbar, ToolbarRow, ToolbarSection, ToolbarTitle} from 'react-mdc-web'

export class Header extends React.Component {
  render () {
    return (
      <Toolbar>
        <ToolbarRow>
          <ToolbarSection align="start">
            <ToolbarTitle>Reason Events</ToolbarTitle>
          </ToolbarSection>
        </ToolbarRow>
      </Toolbar>
    )
  }
}

export default Header
