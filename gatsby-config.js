module.exports = {
  siteMetadata: {
    title: 'Reason Events',
    author: 'Brandon Konkle',
    description: 'An index of Reason-related events.',
    siteUrl: 'https://ecliptic.github.io/reason-events/',
  },
  plugins: [
    'gatsby-plugin-glamor',
    'gatsby-plugin-react-helmet',
    'gatsby-plugin-sharp',
    'gatsby-transformer-sharp',
    'gatsby-plugin-feed',
    'gatsby-plugin-offline',
    // Load images from the filesystem and make them available in the GraphQL data store
    {
      resolve: 'gatsby-source-filesystem',
      options: {
        name: 'images',
        path: `${__dirname}/static/images`,
      },
    },
  ],
}
