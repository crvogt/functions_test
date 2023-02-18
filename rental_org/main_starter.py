'''
HOUSE CLASS OBJECT
# Details of each house
Houses
    -RENT AMOUNT
    -INSPECTION DATES
        -Roof
        -Floors
    -INSURANCE DETAILS
    -EXPENSES
        -Insurance
        -Management
        -Upkeep
    -RENT
        -Incoming

MANAGER CLASS OBJECT
# Populate, add, save, plot, data
Import and export details from a csv file.

A house object
Keeps details on each house

A manager object

NOTE: 
    This needs to be usable, easily add data, expenses, etc

    Can possibly output all of this to quickbooks as well

    Read data from command line to open, close, keep track of CSV files.
'''

import matplotlib.pyplot as plt
import csv



class HOUSE_MANAGER:
    def __init__(self):
        print("Initializing house manager...")
        # Keep a list of all houses
        self.house_list = list()

    def add_house(self, house_details):
        print("Adding a house...")
        self.house_list.append(HOUSE(house_details))

    def extract_data_from_csv(self, csv_filename):
        csv.reader(csv_filename)
        pass

    def write_data_to_csv(self):
        csv.writer(csv_filename)
        pass
        
    def plot_data(self):
        pass

class HOUSE:
    def __init__(self, house_details):
        # House details
        self.address_num = 0
        self.address_street = ""
        self.address_city = ""
        self.rent_amount = 0
        self.insurance_carrier = ""
        self.manager = ""
        
        # House expenses
        self.insurance_rate = 0
        self.management_rate = 0
        
        # Past values
        # self.rent_dict = dict()
        # self.expense_dict = dict()

        # Note
        self.note = ""


house_details = dict()
house_details['address_num'] = 1519
house_mng = HOUSE_MANAGER()
house_mng.add_house(house_details)
