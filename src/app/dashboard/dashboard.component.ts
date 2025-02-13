import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ControllerComponent } from '../controller/controller.component';
import { ChartComponent } from '../chart/chart.component';

@Component({
  selector: 'app-dashboard',
  standalone: true,
  imports: [CommonModule, ControllerComponent, ChartComponent],
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.css']
})
export class DashboardComponent {}