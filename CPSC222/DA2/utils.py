# Mason Manca
# CPSC 222
# Dr.Sprint
# 9/27/21
def read_data(filename):
   data = []
   infile = open(filename, "r")
   headers = infile.readline()
   lines = infile.readlines()
   cleaned_lines = clean_Lines(lines)

   for line in cleaned_lines:
       vals = line.split(",")
       data.append(vals)
   data = remove_whitespace(data)
   infile.close()

   return(headers,data)

def display_table(headers,data):
    for col in headers:
        for dat in data:
            print(dat, end = " " )
        print()

#def get_column(headers, col_name, data):

def clean_Lines(lines):
    for i in range(len(lines)):
        lines[i] = lines[i].strip()
    return lines

def remove_whitespace(data):
    for row in data:
        for i in range(len(row)):
            row[i] = row[i].strip()
    return data

def convert_column_to_numeric(data, column_idx):
    for row in data:
        row[column_idx] = int(row[column_idx])
    