import gmplot


# Function to plot coordinates on Google Maps
def plot_coordinates_on_map(coordinates):
    # Extract latitude and longitude values from coordinates
    lngs, lats = zip(*coordinates)

    # Create a Google Maps plot centered at the first coordinate

    gmap = gmplot.GoogleMapPlotter(lats[0], lngs[0], 16)

    # Add markers for each coordinate
    gmap.marker(lats[0], lngs[0])
    gmap.plot(lats, lngs, 'blue', edge_width=5)
    gmap.marker(lats[-1], lngs[-1], color='grey', title='First Point')
    # Generate an HTML file containing the map
    gmap.draw("map.html")
    print("Map saved as 'map.html'.")

# Example usage with given points
points = [
]
# Plot coordinates on the map
plot_coordinates_on_map(points)
