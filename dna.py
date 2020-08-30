from collections import defaultdict
from csv import DictReader
import re
import sys

def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit()
    with open(sys.argv[1], 'r') as csv_file:
        reader = DictReader(csv_file)
        str_count = defaultdict(dict)
        for row in reader:
            for str_name in reader.fieldnames[1:]:
                str_count[row["name"]][str_name] = int(row[str_name])
    with open(sys.argv[2], 'r') as dna_file:
        dna_str = dna_file.read()
    dna_count = defaultdict(dict)
    for str_name in reader.fieldnames[1:]:
        repeats = re.findall(r'((?:{0})+)'.format(str_name), dna_str)
        n = max([len(r) // len(str_name) for r in repeats]) if repeats else 0
        dna_count[str_name] = n
    matches = [name for name in str_count.keys()
               if dict(dna_count) == str_count[name]]
    print(matches[0] if matches else "No match")

main()
