# LUMAbot

Style Guidelines
-	Naming Conventions
	- Camel case
		- Ex: namingConventions
	- Capitalize function names
		- Ex: FunctionOneDef
	- Only use common abbreviations
		- Good Ex: Def, num
		- Bad Ex: It (iterations), wid/len (width/length)
-	Indents/Spaces
	- Indents/Tabs are 4 spaces
		- Ex: 	if (blah == blah)
	- Put a space in between math signs and binary operators
		- Ex: a = b + c 
		- Ex: if (a < b)
-	Braces
	- Each brace should be on its own line.
		- Example function definition: 
			private void ExampleFunction()
			{
				return;
			}
		- Example if statement:
			if (x == 5)
			{
				x = 10;
			}
-	Variable Types
	- Use the smallest variable type needed
		- Good Ex: uint8_t eightBit
		- Bad Ex: int somethingRandom
