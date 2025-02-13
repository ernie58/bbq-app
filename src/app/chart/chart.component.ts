import { Component, OnInit } from '@angular/core';
import { Chart } from 'chart.js';
import { WebSocketService } from '../services/websocket.service';
import { MatCardModule } from '@angular/material/card';

@Component({
  selector: 'app-chart',
  standalone: true,
  imports: [MatCardModule],
  templateUrl: './chart.component.html',
  styleUrls: ['./chart.component.css']
})
export class ChartComponent implements OnInit {
  chart: any;

  constructor(private wsService: WebSocketService) {}

  ngOnInit() {
    this.chart = new Chart('chartCanvas', {
      type: 'line',
      data: { labels: [], datasets: [{ label: 'Temperature', data: [] }] },
    });

    this.wsService.getMessages().subscribe(data => {
      this.chart.data.labels.push(new Date().toLocaleTimeString());
      this.chart.data.datasets[0].data.push(data.currentTemperature);
      this.chart.update();
    });
  }
}