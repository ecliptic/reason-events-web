// @flow
import React from 'react'
import moment from 'moment'
import {connect} from 'react-redux'
import {css} from 'glamor'

import * as EventState from 'state/EventState.bs'

import {
  Button,
  Card,
  CardHeader,
  CardText,
  CardActions,
  CardTitle,
  CardSubtitle,
  Cell,
  Textfield,
  GridList,
  Tile,
  TilePrimary,
  TileTitle,
  TileContent,
  TileSecondary,
  TileSupportText,
} from 'react-mdc-web'

const Styles = {
  container: css({
    margin: '30px',
  }),
  card: css({
    width: '33%',
    marginBottom: '30px',
  }),
  createButton: css({
    marginBottom: '30px',
  }),
}

const initialState = {
  visible: {
    newEvent: false,
  },
  newEvent: {
    name: '',
    date: '',
    eventType: 'DEFAULT',
    location: '',
    descripton: '',
  },
}

// The main component for the home page
class Home extends React.Component {
  state = initialState

  componentDidMount () {
    this.props.refreshEvents()
  }

  toggleNewEvent = (e) => {
    if (e) e.preventDefault()
    const {visible} = this.state
    this.setState({visible: {...visible, newEvent: !visible.newEvent}})
  }

  handleCancelNewEvent = (e) => {
    e.preventDefault()
    this.setState({newEvent: initialState.newEvent})
    this.toggleNewEvent()
  }

  handleChangeField = (field) => ({target: {value}}) => {
    this.setState({newEvent: {...this.state.newEvent, [field]: value}})
  }

  handleSubmitNewEvent = (e) => {
    const {createEvent} = this.props
    const {visible, newEvent} = this.state
    e.preventDefault()
    createEvent(newEvent)
    this.setState({visible: {...visible, newEvent: false}})
  }

  render () {
    const {events} = this.props
    const {visible, newEvent} = this.state
    const {name, date, location, description} = newEvent
    return (
      <div className={Styles.container.toString()}>
        <Card display-if={visible.newEvent} className={Styles.card.toString()}>
          <CardHeader>
            <CardTitle>Create a new Event</CardTitle>
            <CardSubtitle>Tell the community what's going on!</CardSubtitle>
          </CardHeader>
          <CardText>
            <Cell>
              <Textfield
                floatingLabel="Name"
                value={name}
                onChange={this.handleChangeField('name')}
              />
            </Cell>
            <Cell>
              <Textfield
                value={date}
                type="date"
                onChange={this.handleChangeField('date')}
              />
            </Cell>
            <Cell>
              <Textfield
                floatingLabel="Location"
                value={location}
                onChange={this.handleChangeField('location')}
              />
            </Cell>
            <Cell>
              <Textfield
                floatingLabel="Description"
                value={description}
                textarea
                onChange={this.handleChangeField('description')}
              />
            </Cell>
          </CardText>
          <CardActions>
            <Button onClick={this.handleCancelNewEvent}>Cancel</Button>
            <Button onClick={this.handleSubmitNewEvent} raised>Save</Button>
          </CardActions>
        </Card>
        <Button
          className={Styles.createButton.toString()}
          display-if={!visible.newEvent}
          onClick={this.toggleNewEvent}
          raised
        >
          Create a New Event
        </Button>
        <div>
          <GridList twoLineCaption>
            {events.map((event) => (
              <Tile key={event.id}>
                <TilePrimary>
                  <TileContent src="https://kradio3.github.io/react-mdc-web/b5c43031775655bd3ea425d9238d2a01.jpg" />
                </TilePrimary>
                <TileSecondary>
                  <TileTitle>{event.name}</TileTitle>
                  <TileSupportText>{moment(event.date).format('MMMM Do, YYYY')}</TileSupportText>
                </TileSecondary>
              </Tile>
            ))}
          </GridList>
        </div>
      </div>
    )
  }
}

const mapState = (state) => ({
  events: EventState.select.events(state),
})

const dispatchActions = {
  setEvents: EventState.actions.setEvents,
  refreshEvents: EventState.actions.refreshEvents,
  createEvent: EventState.actions.createEvent,
}

export default connect(mapState, dispatchActions)(Home)
