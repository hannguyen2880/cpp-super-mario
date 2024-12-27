import os
import re

def add_plantuml_annotations(file_path):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
    except PermissionError:
        print(f'Permission denied: {file_path}')
        return

    class_name = None
    public_methods = []
    private_attributes = []

    class_pattern = re.compile(r'class\s+(\w+)\s*{')
    public_method_pattern = re.compile(r'\s*public:\s*')
    private_attribute_pattern = re.compile(r'\s*private:\s*')
    method_pattern = re.compile(r'\s*(\w[\w\s\*&<>]*)\s+(\w+)\s*\(.*\)\s*{')
    attribute_pattern = re.compile(r'\s*(\w[\w\s\*&<>]*)\s+(\w+)\s*;')

    in_public_section = False
    in_private_section = False

    for line in lines:
        if class_pattern.match(line):
            class_name = class_pattern.match(line).group(1)
        elif public_method_pattern.match(line):
            in_public_section = True
            in_private_section = False
        elif private_attribute_pattern.match(line):
            in_public_section = False
            in_private_section = True
        elif in_public_section and method_pattern.match(line):
            return_type, method_name = method_pattern.match(line).groups()
            public_methods.append(f'+{return_type.strip()} {method_name}()')
        elif in_private_section and attribute_pattern.match(line):
            attr_type, attr_name = attribute_pattern.match(line).groups()
            private_attributes.append(f'-{attr_type.strip()} {attr_name}')

    if class_name:
        plantuml_annotation = [
            '/**',
            ' * @startuml',
            f' * class {class_name} {{'
        ]
        plantuml_annotation.extend([f' *     {method}' for method in public_methods])
        plantuml_annotation.extend([f' *     {attr}' for attr in private_attributes])
        plantuml_annotation.extend([
            ' * }',
            ' * @enduml',
            ' */'
        ])

        try:
            with open(file_path, 'w') as file:
                file.write('\n'.join(plantuml_annotation) + '\n\n')
                file.writelines(lines)
        except PermissionError:
            print(f'Permission denied: {file_path}')

def process_directories(directories):
    for directory in directories:
        for root, _, files in os.walk(directory):
            print(f'Processing directory: {root}')
            for file in files:
                if file.endswith('.h'):
                    file_path = os.path.join(root, file)
                    print(f'Processing file: {file_path}')
                    add_plantuml_annotations(file_path)
                else:
                    print(f'Skipping file: {file}')

if __name__ == "__main__":
    directories = [
        'src/audio',
        'src/components',
        'src/events',
        'src/game',
        'src/game/state',
        'src/map',
        'src/renderers',
        'src/screens',
        'src/systems/animation',
        'src/systems/camera',
        'src/systems/enemy',
        'src/systems/flag',
        'src/systems/IdsMap',
        'src/systems/physics',
        'src/systems/player',
        'src/systems/score',
        'src/systems/sound',
        'src/systems/tile',
        'src/systems/timer',
        'src/ui'
    ]
    process_directories(directories)