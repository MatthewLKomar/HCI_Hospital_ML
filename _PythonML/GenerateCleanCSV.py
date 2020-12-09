#This file generates a new CSV version of the COVIDMEXICO.csv.

import pandas as pd
chart = pd.read_csv("data/Covidmexico.csv", encoding="ISO-8859-1")
#We need to remove the following cols:
# --> PIAS_NACIONALIDAD
# --> ID_REGISTRO
# --> FECHA_ACTUALIZACTION
#because their data is either: garbage or not needed
keep_col = ['ORIGEN','SECTOR','ENTIDAD_UM','SEXO','ENTIDAD_NAC','ENTIDAD_RES','MUNICIPIO_RES','TIPO_PACIENTE',
            #'FECHA_INGRESO', FECHA_SINTOMAS','FECHA_DEF',
            'INTUBADO','NEUMONIA','EDAD','NACIONALIDAD','EMBARAZO','HABLA_LENGUA_INDIG','INDIGENA',
            'DIABETES', 'EPOC',	'ASMA','INMUSUPR','HIPERTENSION','CARDIOVASCULAR','OBESIDAD','RENAL_CRONICA','TABAQUISMO',
            'OTRO_CASO','TOMA_MUESTRA','RESULTADO_LAB' ,'CLASIFICACION_FINAL','MIGRANTE', 'UCI']#'PAIS_ORIGEN',
#keep_col =['INTUBADO','NEUMONIA','EDAD','EMBARAZO',
#          'DIABETES','ASMA','CARDIOVASCULAR','OBESIDAD', 'UCI','RESULTADO_LAB']
chart = chart[keep_col]
#chart = chart.truncate(after=1000000)
print(chart.shape)
#when then save it to a seperate CSV so we're not destructive.
chart.to_csv("data/CleanedCovidMexico.csv",index=False)