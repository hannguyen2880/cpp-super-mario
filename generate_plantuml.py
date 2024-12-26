import os

def generate_plantuml_file(src_dir, output_file):
    with open(output_file, 'w') as f:
        f.write('@startuml\n')
        for root, _, files in os.walk(src_dir):
            for file in files:
                if file.endswith('.h'):
                    file_path = os.path.join(root, file)
                    f.write(f'!include {file_path}\n')
        f.write('@enduml\n')

if __name__ == "__main__":
    src_directory = 'src'
    output_plantuml_file = 'diagram.plantuml'
    generate_plantuml_file(src_directory, output_plantuml_file)
    print(f'PlantUML file generated: {output_plantuml_file}')