# make sure pip is updated and run "pip install requests" in Bash, otherwise you'll get an error code.
import requests

# Function to get weather data from OpenWeatherMap API
def get_weather(city, api_key):
    base_url = "http://api.openweathermap.org/data/2.5/weather?"
    complete_url = base_url + "q=" + city + "&appid=" + api_key + "&units=metric"
    
    # Send GET request to the API
    response = requests.get(complete_url)
    
    # Check if the city was found (status code 200)
    if response.status_code == 200:
        data = response.json()
        
        # Extract relevant information
        main = data['main']
        temperature = main['temp']
        humidity = main['humidity']
        weather_description = data['weather'][0]['description']
        wind_speed = data['wind']['speed']
        
        # Print the weather details
        print(f"\nWeather in {city.capitalize()}:")
        print(f"Temperature: {temperature}°C")
        print(f"Humidity: {humidity}%")
        print(f"Weather Description: {weather_description}")
        print(f"Wind Speed: {wind_speed} m/s")
    else:
        print("City not found. Please check the city name.")

def main():
    # Get city and API key from the user
    city = input("Enter city name: ")
    api_key = "a7e9ba5f7014f73544aa98978f28ff87"  # Replace with your actual OpenWeatherMap API key
    
    get_weather(city, api_key)

if __name__ == "__main__":
    main()
