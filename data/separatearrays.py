import json

# Load the JSON data
with open('ethnicities.json', 'r') as file:
    data = json.load(file)

# Identify and split the specific field into an array
for item in data:
    item['eyes-color'] = item['eyes-color'].split(',')
    item['skin-color'] = item['skin-color'].split(',')
    item['hair-textures'] = item['hair-textures'].split(',')
    item['hair-colors'] = item['hair-colors'].split(',')

# Save the modified data back to a JSON file
with open('ethnicities.json', 'w') as file:
    json.dump(data, file, separators=(',', ':'))

