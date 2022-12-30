import pandas as pd
from matplotlib import pyplot as plt

headers = ['vertices number', 'average error']

def generate_single_chart(name, data):
    x = data[headers[0]]
    y = data[headers[1]]

    truncated_name = name.removesuffix('.csv')

    plt.plot(x, y, marker='.')
    plt.ticklabel_format(style='plain')
    plt.xlabel(headers[0])
    plt.ylabel(headers[1] + ' [%]')
    plt.title(truncated_name)
    plt.savefig(f'plots/{truncated_name}.png', bbox_inches='tight')
    plt.close()

def generate_summary_chart(data):
    for name, value in data.items():
        x = value[headers[0]]
        y = value[headers[1]]
        plt.plot(x, y, label=name.removesuffix('.csv'), marker='.')

    plt.ticklabel_format(style='plain')
    plt.xlabel(headers[0])    
    plt.ylabel(headers[1] + ' [%]')
    plt.legend()
    plt.title('summary')
    plt.savefig('plots/summary-errors.png', bbox_inches='tight')
    plt.close()

def main():
    files = ['simulated-annealing-errors.csv', 'tabu-search-errors.csv']

    all_data = {}

    for file in files:
        data = pd.read_csv(file, sep=';')
        all_data[file] = data

    for key in all_data.keys():
        generate_single_chart(key, all_data[key])

    generate_summary_chart(all_data)

if __name__ == '__main__':
    main()