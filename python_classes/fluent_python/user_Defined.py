import random

class BingoCage:
	def __init__(self, items):
		self._items = items#list(items)
		print('shuffling items')
		random.shuffle(self._items)


	def pick(self):
		try: 
			print('returning item')
			return self._items.pop()
		except IndexError:
			raise LookupError('pick from empty BingoCage')


	def __call__(self):
		print('in call... returning pick')
		try: 
			print('returning item')
			return self._items.pop()
		except IndexError:
			raise LookupError('pick from empty BingoCage')
		# return self.pick()


val = BingoCage([0, 1, 2, 3, 4])
print(val)
# print(val.pick())
