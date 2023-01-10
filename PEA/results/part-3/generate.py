import pandas as pd
from matplotlib import pyplot as plt

def generate_chart(file_name, files, headers, x_unit = '', y_unit = ''):
    data = {}

    for file in files:
        signle_data = pd.read_csv(file, sep=';')
        data[file] = signle_data
    
    for name, value in data.items():
        x = value[headers[0]]
        y = value[headers[1]]
        truncated_name = name.removesuffix('.csv')
        plot_name = truncated_name.split('-')[-1]
        plt.plot(x, y, label=plot_name, marker='.')

    plt.ticklabel_format(style='plain')
    plt.xlabel(headers[0] + (f' [{x_unit}]' if x_unit != '' else ''))    
    plt.ylabel(headers[1] + (f' [{y_unit}]' if y_unit != '' else ''))
    plt.legend()
    plt.title(file_name.replace('-', ' '))
    plt.savefig(f'plots/{file_name}.png', bbox_inches='tight')
    plt.close()


def crossover_charts():
    headers = ['crossover rate', 'average error']

    files = [
        'genetic-crossover-invert.csv',
        'genetic-crossover-swap.csv',
    ]
    generate_chart('genetic-crossover', files, headers, y_unit='%')


def mutation_charts():
    headers = ['mutation rate', 'average error']

    files = [
        'genetic-mutation-invert.csv',
        'genetic-mutation-swap.csv',
    ]
    generate_chart('genetic-mutation', files, headers, y_unit='%')


def population_charts():
    headers = ['vertices', 'average error']

    files = [
        'genetic-invert-population100.csv',
        'genetic-invert-population200.csv',
        'genetic-invert-population300.csv',
    ]
    generate_chart('genetic-invert-population', files, headers, y_unit='%')

    files = [
        'genetic-swap-population100.csv',
        'genetic-swap-population200.csv',
        'genetic-swap-population300.csv',
    ]
    generate_chart('genetic-swap-population', files, headers, y_unit='%')

def main():
    population_charts()
    mutation_charts()
    crossover_charts()
    
if __name__ == '__main__':
    main()