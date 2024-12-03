from geopy.geocoders import Nominatim
from geopy.distance import geodesic
import sys
import json

def get_city(lat, lon):
    geolocator = Nominatim(user_agent="AStar-GeoCoder")
    try:
        location = geolocator.reverse((lat, lon), exactly_one=True, language="en")
        if location and 'city' in location.raw['address']:
            return location.raw['address']['city']
        elif location and 'town' in location.raw['address']:
            return location.raw['address']['town']
        elif location and 'village' in location.raw['address']:
            return location.raw['address']['village']
        else:
            return find_closest_city(lat, lon)
    except Exception as e:
        return find_closest_city(lat, lon)

def find_closest_city(lat, lon):
    # Load global cities from a dataset
    with open("saudi_cities.json", "r") as file:
        cities = json.load(file)

    closest_city = None
    min_distance = float("inf")

    for city in cities:
        city_coords = (city["latitude"], city["longitude"])
        distance = geodesic((lat, lon), city_coords).kilometers
        if distance < min_distance:
            min_distance = distance
            closest_city = city["name"]

    return closest_city if closest_city else "Unknown"

if __name__ == "__main__":
    latitude = float(sys.argv[1])
    longitude = float(sys.argv[2])
    print(get_city(latitude, longitude))
