import requests

API_KEY = 'e207362362dc640fcac4285b'
BASE_URL = 'https://v6.exchangerate-api.com/v6/'

def get_exchange_rate(base_currency, target_currency):
    url = f"{BASE_URL}{API_KEY}/pair/{base_currency}/{target_currency}"
    response = requests.get(url)
    if response.status_code == 200:
        data = response.json()
        if data['result'] == 'success':
            return data['conversion_rate']
        else:
            print("Error in fetching exchange rate.")
            return None
    else:
        print("Error in network request.")
        return None

def convert_currency(amount, base_currency, target_currency):
    rate = get_exchange_rate(base_currency, target_currency)
    if rate:
        converted_amount = amount * rate
        return converted_amount
    else:
        return None

def format_currency(amount, currency_symbol='$'):
    return f"{currency_symbol}{amount:,.2f}"

if __name__ == '__main__':
    base_currency = input("Enter the base currency (e.g., USD): ").upper()
    target_currency = input("Enter the target currency (e.g., EUR): ").upper()
    
    # Remove commas from the input string and convert it to float
    amount_str = input(f"Enter the amount in {base_currency}: ")
    amount = float(amount_str.replace(',', ''))

    # Format input amount as a readable currency
    readable_amount = format_currency(amount, currency_symbol='$')

    converted_amount = convert_currency(amount, base_currency, target_currency)

    if converted_amount:
        # Format the converted amount as a readable currency
        readable_converted_amount = format_currency(converted_amount, currency_symbol='€' if target_currency == 'EUR' else '')
        print(f"{readable_amount} in {base_currency} is equal to {readable_converted_amount} in {target_currency}.")
    else:
        print("Could not perform the conversion.")