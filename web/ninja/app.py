import os 
from flask import Flask
from flask import request
from flask import render_template
from flask import render_template_string


app = Flask(__name__)
filter_list = ["__class__","__base__","__bases__", "__mro__","__subclasses__",  "config", "[", "]", "__name__", "__main__"] 

execfile('flag.py')

@app.route("/")
def index():
	name = request.args.get('name')
	if name is None:
		return "Empty name"

	print dir(name) 

	for not_allowed_word in filter_list:
		if not_allowed_word in name:
			return "No Hack ~_~  filter word : {}".format(not_allowed_word), 400

	rendered_template = render_template("index.html", name=name)
	return render_template_string(rendered_template)

if __name__ == "__main__":
	app.run(debug=True)
